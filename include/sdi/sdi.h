//
// File: include/sdi/sdi.h
//
// Description: Header for libsdi
//

#if !defined(__INCLUDE_SDI_SDI_H__)
#define __INCLUDE_SDI_SDI_H__

#include <l4/kdebug.h>
#include <sdi/types.h>


// Heap managment
extern void* alloc (L4_Word_t size);
extern void free (void* freeptr);

// Logging
extern void LogMessage (char* message);
extern L4_Word_t IPCSpaceControl (L4_ThreadId_t SpaceSpecifier, L4_Word_t  control, L4_Fpage_t KernelInterfacePageArea, L4_Fpage_t UtcbArea, L4_ThreadId_t Redirector);
extern L4_Word_t IPCThreadControl (L4_ThreadId_t dest, L4_ThreadId_t SpaceSpecifier, L4_ThreadId_t scheduler, L4_ThreadId_t pager, void *UtcbLocation);
// Panic managment 
extern void panic (char* message);

#define bailout(S) L4_KDB_Enter( S )
#define assert(X) if (!(X)) bailout( #X )



#endif /* !__INCLUDE_SDI_SDI_H__ */
