//
// File:  src/root/main.cc
//
// Description: a VERY simple root task for sdi
//

#include <l4/thread.h>
#include <l4/space.h>
#include <l4/message.h>
#include <l4/ipc.h>
#include <l4/sigma0.h>
#include <l4/bootinfo.h>

#include <stdlib.h>

#include <sdi/sdi.h>
#include <sdi/types.h>

#include <l4io.h>
#include <elf.h>
#include "root.h"

#include <idl4glue.h>
#include <if/iflocator.h>
#include <if/iflogging.h>
	
/* local threadids */
L4_ThreadId_t sigma0id;
L4_ThreadId_t pagerid;
L4_ThreadId_t locatorid;
L4_ThreadId_t loggerid;
L4_ThreadId_t syscallid;
L4_ThreadId_t hello1id;
L4_ThreadId_t hello2id;

L4_Word_t pagesize;
L4_Word_t utcbsize;
L4_Fpage_t kiparea;
L4_Fpage_t utcbarea;

/* helperstuff */

extern char __elf_start;
extern char __elf_end;

extern char __heap_start;
extern char __heap_end;


L4_Word_t logger_stack[1024];
L4_Word_t locator_stack[1024];
L4_Word_t hello1_stack[1024];
L4_Word_t hello2_stack[1024];
L4_Word_t syscall_stack[1024];

L4_Word_t ipc_label = 0x101;
L4_Word_t ipc_label_client = 0x103;
L4_Word_t message_buffer[2];
L4_Word_t message_buffer_client;
L4_Word_t adder_messages[2];

L4_ThreadId_t start_thread (L4_ThreadId_t threadid, L4_Word_t ip, L4_Word_t sp, void* utcblocation) {
    printf ("New thread with ip:%lx / sp:%lx\n", ip, sp);
    /* do the ThreadControl call */
    if (!L4_ThreadControl (threadid, L4_Myself (),  L4_Myself (), pagerid,
		      (void*)utcblocation ))
	panic ("ThreadControl failed");
    /* set thread on our code */
    L4_Start (threadid, sp, ip);

    return threadid;
}

L4_ThreadId_t start_task (L4_ThreadId_t threadid, L4_Word_t ip, L4_Fpage_t nutcbarea) {
    printf ("New task with ip:%lx\n", ip);
    /* First ThreadControl to setup initial thread */
    if (!L4_ThreadControl (threadid, threadid, L4_Myself (), L4_nilthread, (void*)-1UL))
	panic ("ThreadControl failed\n");

    L4_Word_t dummy;

    if (!L4_SpaceControl (threadid, 0, L4_FpageLog2 (0xB0000000,14), 
			   utcbarea, L4_anythread, &dummy))
	panic ("SpaceControl failed\n");

    /* Second ThreadControl, activate thread */
    if (!L4_ThreadControl (threadid, threadid, L4_nilthread, L4_Myself (), 
			   (void*)L4_Address (nutcbarea)))
	panic ("ThreadControl failed\n");

    /* send startup IPC */
    L4_Msg_t msg;
    L4_Clear (&msg);
    L4_Append (&msg, ip);
    L4_Append (&msg, (0));
    L4_Load (&msg);
    L4_Send (threadid);

    return threadid;
}

L4_Bool_t request_page (L4_Word_t addr) {
    return !(L4_IsNilFpage (L4_Sigma0_GetPage (sigma0id,
					       L4_Fpage (addr, pagesize))));
}

void list_modules (const L4_BootInfo_t* bootinfo) {
    L4_BootRec_t* bootrec = L4_BootInfo_FirstEntry (bootinfo);
    for (unsigned int i=0; i < L4_BootInfo_Entries (bootinfo); i++) {
	printf ("Module: start %lx size %lx type: %d\n", 
		L4_Module_Start (bootrec),
		L4_Module_Size (bootrec),
		(int)L4_Type (bootrec));
	bootrec = L4_Next (bootrec);
    }
}

L4_BootRec_t* find_module (unsigned int index, const L4_BootInfo_t* bootinfo) {
    if (L4_BootInfo_Entries (bootinfo) < index) 
	panic ("Some modules are missing");
    L4_BootRec_t* bootrec = L4_BootInfo_FirstEntry (bootinfo);
    for (unsigned int i = 0; i < index; i++)
	bootrec = L4_Next (bootrec);
    return bootrec;
}

L4_Word_t load_elfimage (L4_BootRec_t* mod) {
    /* Check type of module */
    if (L4_Type (mod) != L4_BootInfo_Module)
	panic ("Wrong module type");
    /* Bring in the memory from sigma0 */
    for (L4_Word_t addr = L4_Module_Start (mod); 
	 addr < L4_Module_Start (mod) + L4_Module_Size (mod); 
	 addr += pagesize) 
	if (!request_page (addr)) {
	    panic ("could not get module pages from sigma0");
	}
    
    Elf32_Ehdr* hdr = (Elf32_Ehdr*)L4_Module_Start (mod);
    Elf32_Phdr* phdr;
    if ((hdr->e_ident[EI_MAG0] !=  ELFMAG0) || 
	(hdr->e_ident[EI_MAG1] !=  ELFMAG1) || 
	(hdr->e_ident[EI_MAG2] !=  ELFMAG2) ||
	(hdr->e_ident[EI_MAG3] !=  ELFMAG3)) {
	return NULL;
    }
    if (hdr->e_type != ET_EXEC) { return NULL; }
    if (hdr->e_machine != EM_386) { return NULL; }
    if (hdr->e_version != EV_CURRENT) { return NULL; }
    if (hdr->e_flags != 0) { return NULL; }
    phdr = (Elf32_Phdr *) (hdr->e_phoff + (unsigned int) hdr);
    if (hdr->e_phnum <= 0) {
	return NULL;
    }
    for (int i = 0; i < hdr->e_phnum; i++) {
	if (phdr[i].p_type == PT_LOAD) {
	    L4_Word_t fstart, mstart;
	    /* found a loadable section */

	    /* figure out the start and end of image in the "file" */
	    fstart = (L4_Word_t)hdr + phdr[i].p_offset;

	    /* figure out the start and end of the final image in memory */
	    mstart =  phdr[i].p_vaddr;

	    printf ("Module psection: fstart: %lx -> mstart: %lx\n", fstart, mstart);

	    /* copy the image of the file */
	    memcpy((void*) mstart, (void*) fstart, phdr[i].p_filesz);

	    /* zero fill the rest(if any) of the destination region */
	    memset((void*)(mstart+phdr[i].p_filesz),0,phdr[i].p_memsz - phdr[i].p_filesz);
	}
    }
    return (hdr->e_entry);
}


#define UTCBaddress(x) ((void*)(((L4_Word_t)L4_MyLocalId().raw + utcbsize * (x)) & ~(utcbsize - 1)))

/* Sends IPC to thread dest with first n message from array messages */

void SendIPC(L4_ThreadId_t dest, L4_Word_t label, L4_Word_t* messages, int n){
	L4_Msg_t message; 
	L4_Clear(&message);
	L4_Set_Label(&message, label);

	for (int i=0; i < n; i++){
		L4_Append(&message, messages[i]);
	}

	L4_Load(&message);
	L4_Send(dest);
}

/* Listens for an incoming IPC, stores result in array rcvd up to n elements */
void ListenIPC(L4_Word_t* rcvd, int n, L4_Word_t id){
  L4_ThreadId_t tid;
  L4_MsgTag_t tag;
  L4_Msg_t buf; 
  L4_Word_t lbl=0;

  do{
    L4_Clear(&buf);
    tag=L4_Wait(&tid);
    L4_Store(tag, &buf);
  } while(L4_Label(&buf) != id);

	for (int i=0; i < n; i++){ 
	  rcvd[i] = L4_Get(&buf, i);
	}
	
  L4_Clear(&buf);
  L4_Reply(tid);
}

void hello_server(void){
	 /* Guess locatorid */
    locatorid = L4_GlobalId (L4_ThreadIdUserBase (L4_KernelInterface ()) + 3, 1);

    CORBA_Environment env (idl4_default_environment);    
    L4_ThreadId_t logger_id = L4_nilthread;


    printf ("Resolve logger ...\n");
    while (L4_IsNilThread (loggerid)) {
        IF_LOCATOR_Locate ((CORBA_Object)locatorid, IF_LOGGING_ID, &logger_id, &env);
    }
 
	char outbuf[256];
	int r = snprintf(outbuf, sizeof(outbuf), "Hello world no %lx\n", L4_Myself ().raw);
	
	if (r > 0)
		 /* Printout message through logger */
    IF_LOGGING_LogMessage ((CORBA_Object)loggerid, outbuf, &env);
   
		
	while(1){ }
}

/* Client code for adder, also does hello world thread */
void adder_client(void){
	
	// Send 4 and 2 to be added
	adder_messages[0] = 4;
	adder_messages[1] = 2;
	
	// Send operands for addition
	SendIPC(hello1id, ipc_label, adder_messages, 2);
	ListenIPC(&message_buffer_client, 1, ipc_label_client);\
	
	// Should use logmessage but I don't want to have to do a snprintf
	printf("ADDER_CLIENT RECEIVED: %i", message_buffer[0]);
	hello_server();
}


/* Server code for addition expirement, also does hello world thread */
void adder_server(void){
	ListenIPC(message_buffer, 2, ipc_label);
	printf("ADDER_SERVER RECEIVED: %i", message_buffer[0]);
	printf("ADDER_SERVER RECEIVED: %i", message_buffer[1]);
	
	// Do addition and send back result
	message_buffer[0] = message_buffer[0] + message_buffer[1];
	SendIPC(hello2id, ipc_label_client, message_buffer, 2);
	hello_server();
}

int main(void) {
    L4_KernelInterfacePage_t* kip = (L4_KernelInterfacePage_t*)L4_KernelInterface ();

    pagerid = L4_Myself ();
    sigma0id = L4_Pager ();
    locatorid = L4_nilthread;
    
    loggerid = L4_nilthread;

    printf ("Early system infos:\n");
    printf ("Threads: Myself:%lx Sigma0:%lx\n", L4_Myself ().raw, L4_Pager ().raw);
    pagesize = 1 << lsBit (L4_PageSizeMask (kip));
    printf ("Pagesize: %d\n", (int)pagesize);
    kiparea = L4_FpageLog2 ((L4_Word_t)kip, L4_KipAreaSizeLog2 (kip));
    printf ("KernelInterfacePage: %lx size: %d\n", L4_Address (kiparea), (int)L4_Size (kiparea));
    printf ("Bootinfo: %lx\n", L4_BootInfo (kip));
    printf ("ELFimage: from %p to %p\n", &__elf_start, &__elf_end);
    printf ("Heap: start: %p end: %p\n", &__heap_start, &__heap_end);
    utcbsize = L4_UtcbSize (kip);

    utcbarea = L4_FpageLog2 ((L4_Word_t) L4_MyLocalId ().raw,
			      L4_UtcbAreaSizeLog2 (kip) + 1);

    /* startup our locator */
    printf ("Starting locator ...\n");
    /* Generate some threadid */
    locatorid = L4_GlobalId ( L4_ThreadNo (L4_Myself ()) + 1, 1);
    start_thread (locatorid, 
		  (L4_Word_t)&locator_server, 
		  (L4_Word_t)&locator_stack[1023], 
		  UTCBaddress(1) ); 
    printf ("Started with id %lx\n", locatorid.raw);

    /* startup our logger, to be able to put messages on the screen */
    printf ("Starting logger ... \n");
    /* Generate some threadid */
    loggerid = L4_GlobalId ( L4_ThreadNo (L4_Myself ()) + 2, 1);
    start_thread (loggerid, 
		  (L4_Word_t)&logger_server, 
		  (L4_Word_t)&logger_stack[1023], 
		  UTCBaddress(2) ); 
    printf ("Started with id %lx\n", loggerid.raw);

    /* startup our logger, to be able to put messages on the screen */
    printf ("Starting syscall server ... \n");
    /* Generate some threadid */
    syscallid = L4_GlobalId ( L4_ThreadNo (L4_Myself ()) + 7, 1);
    start_thread (syscallid, 
		  (L4_Word_t)&syscall_server, 
		  (L4_Word_t)&syscall_stack[1023], 
		  UTCBaddress(7) ); 
    printf ("Started with id %lx\n", syscallid.raw);
		/* Start a hello world thread */
		printf ("Starting hello world threads ...\n");
		
		hello1id = L4_GlobalId( L4_ThreadNo (L4_Myself()) + 3, 1);
		start_thread (hello1id,
				(L4_Word_t)&adder_server,
				(L4_Word_t)&hello1_stack[1023],
				UTCBaddress(3) );
		printf ("Started with id %lx\n", hello1id.raw);
		
		hello2id = L4_GlobalId( L4_ThreadNo (L4_Myself()) + 4, 1);
		start_thread (hello2id,
				(L4_Word_t)&adder_client,
				(L4_Word_t)&hello2_stack[1023],
				UTCBaddress(4) );
		printf ("Started with id %lx\n", hello2id.raw);
    
    /* We just bring the in the memory of the bootinfo page */
    if (!request_page (L4_BootInfo (L4_KernelInterface ()))) {
	// no bootinfo, no chance, no future. Break up
	panic ("Was not able to get bootinfo");
    }
    /* Quick check */
    if (!L4_BootInfo_Valid ((void*)L4_BootInfo (L4_KernelInterface ()))) 
	panic ("Bootinfo not found");
    list_modules ((L4_BootInfo_t*)L4_BootInfo (L4_KernelInterface ()));

    /* Now we search for the third module, 
       which will (hopefully) be our testclient */ 
    printf("Starting test clients ...\n");
    L4_BootRec_t* module = find_module (2, (L4_BootInfo_t*)L4_BootInfo (L4_KernelInterface ()));
    L4_Word_t startip = load_elfimage (module); 

    /* some ELF loading and staring */

    L4_ThreadId_t testid = L4_GlobalId ( L4_ThreadNo (L4_Myself ()) + 5, 1);
    start_task (testid, startip, utcbarea);
    printf ("Testclient 1 started with as %lx\n", testid.raw);


    printf("Starting test clients ...\n");
    L4_BootRec_t* module2 = find_module (3, (L4_BootInfo_t*)L4_BootInfo (L4_KernelInterface ()));
    L4_Word_t startip2 = load_elfimage (module2); 

    L4_ThreadId_t testid2 = L4_GlobalId ( L4_ThreadNo (L4_Myself ()) + 6, 1);
    start_task (testid2, startip2, utcbarea);
    printf ("Testclient 2 started with as %lx\n", testid2.raw);

		/* now it is time to become the pager for all those threads we 
       created recently */
    pager_loop();

    panic ("Unexpected return from PagerLoop()");
}
