//
// File:  src/test/main.cc
//
// Description: Testclient
//

#include <l4/thread.h>
#include <l4io.h>

#include <sdi/types.h>
#include <sdi/sdi.h>

#include <idl4glue.h>
#include <if/iflocator.h>
#include <if/iflogging.h>


#define UTCBaddress(x) ((void*)(((L4_Word_t)L4_MyLocalId().raw + utcbsize * (x)) & ~(utcbsize - 1)))

L4_Word_t hello1_stack[1024];
L4_ThreadId_t locatorid; 

void hello_server(void){
	LogMessage("Hello test");
	while(1){ }
}

L4_ThreadId_t my_start_thread (L4_ThreadId_t threadid, L4_Word_t ip, L4_Word_t sp, void* utcblocation) {
   // printf ("New thread with ip:%lx / sp:%lx\n", ip, sp);
    /* do the ThreadControl call */
   IPCThreadControl (threadid, L4_Myself (),  L4_Myself (), L4_Myself(),
		      (void*)utcblocation );
		      
    /* set thread on our code */
    L4_Start (threadid, sp, ip);

    return threadid;
}

int main () {
    printf ("Testclient is alive\n");
    
    /* Guess locatorid */
    locatorid = L4_GlobalId (L4_ThreadIdUserBase (L4_KernelInterface ()) + 3, 1);

    CORBA_Environment env (idl4_default_environment);    
    L4_ThreadId_t loggerid = L4_nilthread;

    printf ("Resolve logger ...\n");
    while (L4_IsNilThread (loggerid)) {
        IF_LOCATOR_Locate ((CORBA_Object)locatorid, IF_LOGGING_ID, &loggerid, &env);
    }

   	char outbuf[256];
		int r = snprintf(outbuf, sizeof(outbuf), "Testclient no 1 with TID=%lx\n", L4_Myself ().raw);
	
		if (r > 0)
		 /* Printout message through logger */
   	 IF_LOGGING_LogMessage ((CORBA_Object)loggerid, outbuf, &env);
    
    /* Now try our sdi lib */
    LogMessage ("Hello this is your lib");

 		L4_KernelInterfacePage_t* kip = (L4_KernelInterfacePage_t*)L4_KernelInterface ();
		L4_Word_t utcbsize = L4_UtcbSize (kip);
		L4_ThreadId_t hello1id = L4_GlobalId( L4_ThreadNo (L4_Myself()) + 1, 1);
		my_start_thread (hello1id,
				(L4_Word_t)&hello_server,
				(L4_Word_t)&hello1_stack[1023],
				UTCBaddress(1) );
				
    /* Spin forever */
    while (42);
    
    return 0;
}
