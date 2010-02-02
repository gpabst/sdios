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

L4_ThreadId_t locatorid; 

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
			int r = snprintf(outbuf, sizeof(outbuf), "Testclient no 2 with TID=%lx\n", L4_Myself ().raw);
	
		if (r > 0)
			 /* Printout message through logger */
  	  IF_LOGGING_LogMessage ((CORBA_Object)loggerid, outbuf, &env);
    /* Now try our sdi lib */
    LogMessage ("Hello this is your lib");

    /* Spin forever */
    while (42);
    
    return 0;
}
