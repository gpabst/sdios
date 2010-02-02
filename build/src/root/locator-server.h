/*****************************************************************
 * DO NOT EDIT - MACHINE-GENERATED FILE!
 * 
 * Source file : ../../../src/root/locator.idl
 * Platform    : V4 Generic
 * Mapping     : CORBA C
 * 
 * Generated by IDL4 1.1.0 (roadrunner) on 01/02/2010 20:51
 * Report bugs to haeberlen@ira.uka.de
 *****************************************************************/

#if !defined(__locator_server_h__)
#define __locator_server_h__

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

void  IF_LOCATOR_server();
void  IF_LOCATOR_discard();

#define IF_LOCATOR_DEFAULT_VTABLE { (void*)&service_IF_LOCATOR_Announce, (void*)&service_IF_LOCATOR_Locate }
#define IF_LOCATOR_DEFAULT_VTABLE_SIZE 2
#define IF_LOCATOR_MAX_FID 1
#define IF_LOCATOR_MSGBUF_SIZE 0
#define IF_LOCATOR_STRBUF_SIZE 0
#define IF_LOCATOR_FID_MASK 0x1

typedef union {
  struct {
    idl4_word_t  _msgtag;
    L4_ThreadId_t  thread;
    interfaceid_t  type;
  }  _in;
  struct {
    idl4_word_t  _spacer[64];
    idl4_word_t  _msgtag;
  }  _out;
  struct {
    idl4_word_t  _spacer[64];
    idl4_word_t  _msgtag;
  }  _exc0;
  struct {
    idl4_word_t  _spacer[128];
    idl4_inverse_stringitem  _str[16];
    idl4_word_t  _acceptor;
  }  _buf;
}  _param_IF_LOCATOR_Announce;

idl4_word_t  service_IF_LOCATOR_Announce(idl4_threadid_t  _caller, _param_IF_LOCATOR_Announce * _par);

inline void  IF_LOCATOR_Announce_implementation(CORBA_Object  _caller, const interfaceid_t  type, const L4_ThreadId_t * thread, idl4_server_environment * _env);

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

#define IDL4_PUBLISH_IF_LOCATOR_ANNOUNCE(_func) idl4_word_t  service_IF_LOCATOR_Announce(idl4_threadid_t  _caller, _param_IF_LOCATOR_Announce * _par)\
\
{ \
  idl4_server_environment  _env; \
\
  _env._action = 0;\
\
  /* invoke service */ \
   \
  _func(_caller, _par->_in.type, &_par->_in.thread, &_env);\
\
  if (IDL4_EXPECT_TRUE(_env._action == 0)) \
    { \
      /* jump back */ \
       \
      _par->_out._msgtag = (0 << 6)+0;\
      return 0; \
    } \
\
  /* handle exceptions */ \
   \
  if (_env._action == CORBA_USER_EXCEPTION+(ex_type_conflict << 8)) \
    { \
      _par->_out._msgtag = (_env._action << 16)+(0 << 6)+0;\
      return 0; \
    } \
\
  return 4294967295U; \
} \

#define IDL4_PUBLISH_IF_LOCATOR_Announce IDL4_PUBLISH_IF_LOCATOR_ANNOUNCE

static inline void  IF_LOCATOR_Announce_reply(CORBA_Object  _client)

{
  struct _reply_buffer {
    struct {
      idl4_word_t  _msgtag;
    }  _out;
  }  _buf;
  struct _reply_buffer * _par = &_buf;

  /* send message */
  
  _buf._out._msgtag = 0;
  L4_MsgLoad((L4_Msg_t *)((void*)_par));
  L4_Send_Timeout(_client, L4_ZeroTime);
}

typedef union {
  struct {
    idl4_word_t  _msgtag;
    interfaceid_t  type;
  }  _in;
  struct {
    idl4_word_t  _spacer[64];
    idl4_word_t  _msgtag;
    L4_ThreadId_t  thread;
  }  _out;
  struct {
    idl4_word_t  _spacer[128];
    idl4_inverse_stringitem  _str[16];
    idl4_word_t  _acceptor;
  }  _buf;
}  _param_IF_LOCATOR_Locate;

idl4_word_t  service_IF_LOCATOR_Locate(idl4_threadid_t  _caller, _param_IF_LOCATOR_Locate * _par);

inline void  IF_LOCATOR_Locate_implementation(CORBA_Object  _caller, const interfaceid_t  type, L4_ThreadId_t * thread, idl4_server_environment * _env);

// Channel 0:                        ID OFFS SIZE ALGN FLAGS BUF
//   R0: idl4_word_t  _msgtag         4    0    4    4 -p---  -1
//   R4: interfaceid_t  type          2    4    1    1 x----  -1
// 
// Channel 1:                        ID OFFS SIZE ALGN FLAGS BUF
//   R0: idl4_word_t  _msgtag         5    0    4    4 -p---  -1
//   R4: L4_ThreadId_t  thread        3    4    8    4 x----  -1

#define IDL4_PUBLISH_IF_LOCATOR_LOCATE(_func) idl4_word_t  service_IF_LOCATOR_Locate(idl4_threadid_t  _caller, _param_IF_LOCATOR_Locate * _par)\
\
{ \
  idl4_server_environment  _env; \
\
  _env._action = 0;\
\
  /* invoke service */ \
   \
  _func(_caller, _par->_in.type, &_par->_out.thread, &_env);\
\
  if (IDL4_EXPECT_TRUE(_env._action == 0)) \
    { \
      /* marshal */ \
       \
      _par->_out.thread = _par->_out.thread;\
\
      /* jump back */ \
       \
      _par->_out._msgtag = (0 << 6)+2;\
      return 2; \
    } \
\
  return 4294967295U; \
} \

#define IDL4_PUBLISH_IF_LOCATOR_Locate IDL4_PUBLISH_IF_LOCATOR_LOCATE

static inline void  IF_LOCATOR_Locate_reply(CORBA_Object  _client, L4_ThreadId_t * thread)

{
  struct _reply_buffer {
    struct {
      idl4_word_t  _msgtag;
      L4_ThreadId_t  thread;
    }  _out;
  }  _buf;
  struct _reply_buffer * _par = &_buf;

  /* marshal reply */
  
  _par->_out.thread = *thread;

  /* send message */
  
  _buf._out._msgtag = 2;
  L4_MsgLoad((L4_Msg_t *)((void*)_par));
  L4_Send_Timeout(_client, L4_ZeroTime);
}

/* Interface locator */

void  locator_server();
void  locator_discard();

#define LOCATOR_DEFAULT_VTABLE_2 { (void*)&service_locator_Announce, (void*)&service_locator_Locate }
#define LOCATOR_DEFAULT_VTABLE_DISCARD { (void*)&locator_discard, (void*)&locator_discard }
#define LOCATOR_DEFAULT_VTABLE_SIZE 2
#define LOCATOR_MAX_FID 1
#define LOCATOR_MSGBUF_SIZE 0
#define LOCATOR_STRBUF_SIZE 0
#define LOCATOR_FID_MASK 0x1
#define LOCATOR_IID_MASK 0x3

// Inherited from IF_LOCATOR

typedef union {
  struct {
    idl4_word_t  _msgtag;
    L4_ThreadId_t  thread;
    interfaceid_t  type;
  }  _in;
  struct {
    idl4_word_t  _spacer[64];
    idl4_word_t  _msgtag;
  }  _out;
  struct {
    idl4_word_t  _spacer[64];
    idl4_word_t  _msgtag;
  }  _exc0;
  struct {
    idl4_word_t  _spacer[128];
    idl4_inverse_stringitem  _str[16];
    idl4_word_t  _acceptor;
  }  _buf;
}  _param_locator_Announce;

idl4_word_t  service_locator_Announce(idl4_threadid_t  _caller, _param_locator_Announce * _par);

inline void  locator_Announce_implementation(CORBA_Object  _caller, const interfaceid_t  type, const L4_ThreadId_t * thread, idl4_server_environment * _env);

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

#define IDL4_PUBLISH_LOCATOR_ANNOUNCE(_func) idl4_word_t  service_locator_Announce(idl4_threadid_t  _caller, _param_locator_Announce * _par)\
\
{ \
  idl4_server_environment  _env; \
\
  _env._action = 0;\
\
  /* invoke service */ \
   \
  _func(_caller, _par->_in.type, &_par->_in.thread, &_env);\
\
  if (IDL4_EXPECT_TRUE(_env._action == 0)) \
    { \
      /* jump back */ \
       \
      _par->_out._msgtag = (0 << 6)+0;\
      return 0; \
    } \
\
  /* handle exceptions */ \
   \
  if (_env._action == CORBA_USER_EXCEPTION+(ex_type_conflict << 8)) \
    { \
      _par->_out._msgtag = (_env._action << 16)+(0 << 6)+0;\
      return 0; \
    } \
\
  return 4294967295U; \
} \

#define IDL4_PUBLISH_locator_Announce IDL4_PUBLISH_LOCATOR_ANNOUNCE

static inline void  locator_Announce_reply(CORBA_Object  _client)

{
  struct _reply_buffer {
    struct {
      idl4_word_t  _msgtag;
    }  _out;
  }  _buf;
  struct _reply_buffer * _par = &_buf;

  /* send message */
  
  _buf._out._msgtag = 0;
  L4_MsgLoad((L4_Msg_t *)((void*)_par));
  L4_Send_Timeout(_client, L4_ZeroTime);
}

// Inherited from IF_LOCATOR

typedef union {
  struct {
    idl4_word_t  _msgtag;
    interfaceid_t  type;
  }  _in;
  struct {
    idl4_word_t  _spacer[64];
    idl4_word_t  _msgtag;
    L4_ThreadId_t  thread;
  }  _out;
  struct {
    idl4_word_t  _spacer[128];
    idl4_inverse_stringitem  _str[16];
    idl4_word_t  _acceptor;
  }  _buf;
}  _param_locator_Locate;

idl4_word_t  service_locator_Locate(idl4_threadid_t  _caller, _param_locator_Locate * _par);

inline void  locator_Locate_implementation(CORBA_Object  _caller, const interfaceid_t  type, L4_ThreadId_t * thread, idl4_server_environment * _env);

// Channel 0:                        ID OFFS SIZE ALGN FLAGS BUF
//   R0: idl4_word_t  _msgtag         4    0    4    4 -p---  -1
//   R4: interfaceid_t  type          2    4    1    1 x----  -1
// 
// Channel 1:                        ID OFFS SIZE ALGN FLAGS BUF
//   R0: idl4_word_t  _msgtag         5    0    4    4 -p---  -1
//   R4: L4_ThreadId_t  thread        3    4    8    4 x----  -1

#define IDL4_PUBLISH_LOCATOR_LOCATE(_func) idl4_word_t  service_locator_Locate(idl4_threadid_t  _caller, _param_locator_Locate * _par)\
\
{ \
  idl4_server_environment  _env; \
\
  _env._action = 0;\
\
  /* invoke service */ \
   \
  _func(_caller, _par->_in.type, &_par->_out.thread, &_env);\
\
  if (IDL4_EXPECT_TRUE(_env._action == 0)) \
    { \
      /* marshal */ \
       \
      _par->_out.thread = _par->_out.thread;\
\
      /* jump back */ \
       \
      _par->_out._msgtag = (0 << 6)+2;\
      return 2; \
    } \
\
  return 4294967295U; \
} \

#define IDL4_PUBLISH_locator_Locate IDL4_PUBLISH_LOCATOR_LOCATE

static inline void  locator_Locate_reply(CORBA_Object  _client, L4_ThreadId_t * thread)

{
  struct _reply_buffer {
    struct {
      idl4_word_t  _msgtag;
      L4_ThreadId_t  thread;
    }  _out;
  }  _buf;
  struct _reply_buffer * _par = &_buf;

  /* marshal reply */
  
  _par->_out.thread = *thread;

  /* send message */
  
  _buf._out._msgtag = 2;
  L4_MsgLoad((L4_Msg_t *)((void*)_par));
  L4_Send_Timeout(_client, L4_ZeroTime);
}

#endif /* !defined(__locator_server_h__) */
