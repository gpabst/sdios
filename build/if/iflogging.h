/*****************************************************************
 * DO NOT EDIT - MACHINE-GENERATED FILE!
 * 
 * Source file : ../../if/iflogging.idl
 * Platform    : V4 Generic
 * Mapping     : CORBA C
 * 
 * Generated by IDL4 1.1.0 (roadrunner) on 09/02/2010 18:51
 * Report bugs to haeberlen@ira.uka.de
 *****************************************************************/

#if !defined(__iflogging_h__)
#define __iflogging_h__

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

/* Interface IF_LOGGING */

#if !defined(_objdef___IF_LOGGING)
#define _objdef___IF_LOGGING
typedef CORBA_Object  IF_LOGGING;
#endif /* !defined(_objdef___IF_LOGGING) */

// Channel 0:                        ID OFFS SIZE ALGN FLAGS BUF
//   R0: idl4_word_t  _msgtag         3    0    4    4 -p---  -1
//   R4: idl4_word_t  _message_size   2    4    4    4 x----  -1
//   M0: char _varbuf                 5    0  256    4 -----  -1
//   M-: CORBA_char  _message_buf     2   -1  256    1 x----  -1
//   S0: char message                 2    0  256    1 -----   0
// 
// Channel 1:                        ID OFFS SIZE ALGN FLAGS BUF
//   R-: idl4_word_t  _msgtag         4   -1    4    4 -p---  -1

#if !defined(_funcdef___IF_LOGGING_LogMessage)
#define _funcdef___IF_LOGGING_LogMessage
static inline void  IF_LOGGING_LogMessage(IF_LOGGING  _service, const logmessage_t  message, CORBA_Environment * _env)

{
  idl4_word_t  _exception;
  idl4_word_t  g1;
  idl4_word_t  _memvaridx = 0;
  union {
    struct {
      CORBA_char  _varbuf[256];
    }  _in;
  }  _memmsg;
  L4_MsgTag_t  _result;
  L4_ThreadId_t  _dummy;
  union _buf {
    struct {
      idl4_word_t  _msgtag;
      idl4_word_t  _message_size;
      idl4_stringitem  _memmsg;
    }  _in;
    struct {
      idl4_word_t  _msgtag;
    }  _out;
  }  _pack;

  /* marshal */
  
  g1 = idl4_strlen1(message);
  idl4_memcpy(&_memmsg._in._varbuf[_memvaridx], message, ((g1+3)) >> 2);
  _memvaridx += ((g1+3) & 0xFFFFFFFCU);
  _pack._in._message_size = g1;

  /* invoke IPC */
  
  _pack._in._memmsg.len = (0+_memvaridx) << 10;
  _pack._in._memmsg.ptr = &_memmsg;
  _pack._in._msgtag = 1+((64U) << 16)+(2 << 6);
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
#endif /* !defined(_funcdef___IF_LOGGING_LogMessage) */

#endif /* !defined(__iflogging_h__) */
