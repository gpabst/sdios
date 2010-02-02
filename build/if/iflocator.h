/*****************************************************************
 * DO NOT EDIT - MACHINE-GENERATED FILE!
 * 
 * Source file : ../../if/iflocator.idl
 * Platform    : V4 Generic
 * Mapping     : CORBA C
 * 
 * Generated by IDL4 1.1.0 (roadrunner) on 01/02/2010 23:52
 * Report bugs to haeberlen@ira.uka.de
 *****************************************************************/

#if !defined(__iflocator_h__)
#define __iflocator_h__

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
#include "sdi/types.h"

#define IF_LOGGING_ID 1

#define IF_LOCATOR_ID 2

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

/* Interface IF_LOCATOR */

#if !defined(_objdef___IF_LOCATOR)
#define _objdef___IF_LOCATOR
typedef CORBA_Object  IF_LOCATOR;
#endif /* !defined(_objdef___IF_LOCATOR) */

// Channel 0:                        ID OFFS SIZE ALGN FLAGS BUF
//   R0: idl4_word_t  _msgtag         4    0    4    4 -p---  -1
//   R4: L4_ThreadId_t  thread        3    4    8    4 x----  -1
//   R12: interfaceid_t  type         2   12    1    1 x----  -1
// 
// Channel 1:                        ID OFFS SIZE ALGN FLAGS BUF
//   R-: idl4_word_t  _msgtag         5   -1    4    4 -p---  -1
// 
// Channel 2:                        ID OFFS SIZE ALGN FLAGS BUF
//   R-: idl4_word_t  _msgtag         6   -1    4    4 -p---  -1

#if !defined(_funcdef___IF_LOCATOR_Announce)
#define _funcdef___IF_LOCATOR_Announce
static inline void  IF_LOCATOR_Announce(IF_LOCATOR  _service, const interfaceid_t  type, const L4_ThreadId_t * thread, CORBA_Environment * _env)

{
  idl4_word_t  _exception;
  L4_MsgTag_t  _result;
  L4_ThreadId_t  _dummy;
  union _buf {
    struct {
      idl4_word_t  _msgtag;
      L4_ThreadId_t  thread;
      interfaceid_t  type;
    }  _in;
    struct {
      idl4_word_t  _msgtag;
    }  _out;
    struct {
      idl4_word_t  _msgtag;
    }  _exc0;
  }  _pack;

  /* marshal */
  
  _pack._in.type = type;
  _pack._in.thread = *thread;

  /* invoke IPC */
  
  _pack._in._msgtag = 3+((128U) << 16);
  L4_MsgLoad((L4_Msg_t *)((void*)&_pack));
  _result = L4_Ipc(_service, _service, (_env == 0) ? L4_Timeouts(L4_Never, L4_Never) : _env->_timeout, &_dummy);
  L4_MsgStore(_result, (L4_Msg_t *)((void*)&_pack));

  _exception = L4_Label(_result);

  if (_env != 0)
    {
      if (!L4_IpcSucceeded(_result))
        *(L4_Word_t*)_env = CORBA_SYSTEM_EXCEPTION+(L4_ErrorCode() << 8);
        else *(L4_Word_t*)_env = _exception;
    }
}
#endif /* !defined(_funcdef___IF_LOCATOR_Announce) */

// Channel 0:                        ID OFFS SIZE ALGN FLAGS BUF
//   R0: idl4_word_t  _msgtag         4    0    4    4 -p---  -1
//   R4: interfaceid_t  type          2    4    1    1 x----  -1
// 
// Channel 1:                        ID OFFS SIZE ALGN FLAGS BUF
//   R0: idl4_word_t  _msgtag         5    0    4    4 -p---  -1
//   R4: L4_ThreadId_t  thread        3    4    8    4 x----  -1

#if !defined(_funcdef___IF_LOCATOR_Locate)
#define _funcdef___IF_LOCATOR_Locate
static inline void  IF_LOCATOR_Locate(IF_LOCATOR  _service, const interfaceid_t  type, L4_ThreadId_t * thread, CORBA_Environment * _env)

{
  idl4_word_t  _exception;
  L4_MsgTag_t  _result;
  L4_ThreadId_t  _dummy;
  union _buf {
    struct {
      idl4_word_t  _msgtag;
      interfaceid_t  type;
    }  _in;
    struct {
      idl4_word_t  _msgtag;
      L4_ThreadId_t  thread;
    }  _out;
  }  _pack;

  /* marshal */
  
  _pack._in.type = type;

  /* invoke IPC */
  
  _pack._in._msgtag = 1+((129U) << 16);
  L4_MsgLoad((L4_Msg_t *)((void*)&_pack));
  _result = L4_Ipc(_service, _service, (_env == 0) ? L4_Timeouts(L4_Never, L4_Never) : _env->_timeout, &_dummy);
  L4_MsgStore(_result, (L4_Msg_t *)((void*)&_pack));

  _exception = L4_Label(_result);

  if (IDL4_EXPECT_TRUE((L4_IpcSucceeded(_result)) && !_exception))
    {
      /* unmarshal */
      
      *thread = _pack._out.thread;
    }

  if (_env != 0)
    {
      if (!L4_IpcSucceeded(_result))
        *(L4_Word_t*)_env = CORBA_SYSTEM_EXCEPTION+(L4_ErrorCode() << 8);
        else *(L4_Word_t*)_env = _exception;
    }
}
#endif /* !defined(_funcdef___IF_LOCATOR_Locate) */

#endif /* !defined(__iflocator_h__) */
