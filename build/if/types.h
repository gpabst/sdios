/*****************************************************************
 * DO NOT EDIT - MACHINE-GENERATED FILE!
 * 
 * Source file : ../../if/types.idl
 * Platform    : V4 Generic
 * Mapping     : CORBA C
 * 
 * Generated by IDL4 1.1.0 (roadrunner) on 16/02/2010 16:22
 * Report bugs to haeberlen@ira.uka.de
 *****************************************************************/

#if !defined(__types_h__)
#define __types_h__

#define IDL4_OMIT_FRAME_POINTER 0
#define IDL4_USE_FASTCALL 0
#define IDL4_NEED_MALLOC 1
#define IDL4_API v4
#define IDL4_ARCH generic

#include "idl4/idl4.h"

#if defined(IDL4_HEADER_REVISION) && IDL4_HEADER_REVISION < 20060813
#error You are using outdated versions of the IDL4 header files
#endif /* defined(IDL4_HEADER_REVISION) && IDL4_HEADER_REVISION < 20060813 */

#include "sdi/types.h"

#define IF_LOGGING_ID 1

#define IF_LOCATOR_ID 2

#define IF_SYSCALL_ID 3

#define MAX_INTERFACEID 8

#if !defined(_typedef___interfaceid_t)
#define _typedef___interfaceid_t
typedef CORBA_char  interfaceid_t;
#endif /* !defined(_typedef___interfaceid_t) */

#if !defined(_typedef___logmessage_t)
#define _typedef___logmessage_t
typedef CORBA_char * logmessage_t;
#endif /* !defined(_typedef___logmessage_t) */

#if !defined(_typedef___buffer_t)
#define _typedef___buffer_t
typedef struct {
  CORBA_unsigned_long  _maximum;
  CORBA_unsigned_long  _length;
  CORBA_char * _buffer;
}  buffer_t;
#endif /* !defined(_typedef___buffer_t) */

#define ex_type_conflict 1

#if !defined(_typedef___type_conflict)
#define _typedef___type_conflict
typedef struct type_conflict  type_conflict;
#endif /* !defined(_typedef___type_conflict) */

#endif /* !defined(__types_h__) */
