//
// File: lib/sdi/logging.cc
//
// Description: Logging messages
//

#include <stdlib.h>

#include <sdi/types.h>
#include <sdi/sdi.h>
#include <l4io.h>
#include <l4/thread.h>

#include <idl4glue.h>
#include <if/iflocator.h>
#include <if/iflogging.h>
void LogMessage (char* message) {
    L4_ThreadId_t locatorid = L4_GlobalId (L4_ThreadIdUserBase (L4_KernelInterface ()) + 3, 1);

    CORBA_Environment env (idl4_default_environment);    
    L4_ThreadId_t loggerid = L4_nilthread;

    while (L4_IsNilThread (loggerid)) {
        IF_LOCATOR_Locate ((CORBA_Object)locatorid, IF_LOGGING_ID, &loggerid, &env);
    }

   	char outbuf[256];
		int r = snprintf(outbuf, sizeof(outbuf), message, L4_Myself ().raw);
	
		if (r > 0)
		 /* Printout message through logger */
   	 IF_LOGGING_LogMessage ((CORBA_Object)loggerid, outbuf, &env);
}
