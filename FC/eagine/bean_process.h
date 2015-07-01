/******************************************************************************

  Copyright (C), 2001-2011, DCN Co., Ltd.

 ******************************************************************************
  File Name     : msg_process.h
  Version       : Initial Draft
  Author        : Eason Lee
  Created       : 2014/9/12
  Last Modified :
  Description   : msg_process.c header file
  Function List :
  History       :
  1.Date        : 2014/9/12
    Author      : Eason Lee
    Modification: Created file

******************************************************************************/

/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * internal routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * project-wide global variables                *
 *----------------------------------------------*/

/*----------------------------------------------*
 * module-wide global variables                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * constants                                    *
 *----------------------------------------------*/

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * routines' implementations                    *
 *----------------------------------------------*/

#ifndef __MSG_PROCESS_H__
#define __MSG_PROCESS_H__

#include "common.h"

#define MSG_LEN_MAX       256

typedef int (*notify)(void*, void*);

typedef struct NOTIFY_LIST
{
    struct NOTIFY_LIST *next ;
    notify notify_to;          /* jsut only used in BEAN_BASE_ON*/
    char   *notify_func_name;
    void   *bean_process;
}NOTIFY_LIST_STRU;


typedef struct BEAN_PROCESS
{
    char           *bean_name;                       /* the string which show to user what is the name of this bean*/
    int            (*update_from_local)(char *);     /* use this fun update the bean(typically the hardware changed */
    int            (*update_to_local)(char * /* local bean*/, char * /* received bean*/); /* 1st.local bean 2se.received bean. when reive the update message, use this fun to update to lower layer*/
    int            (*check_para)(char *);            /* check any value in this bean rightor not */
    int            (*init_bean)(char *);             /* init the bean function */
    NOTIFY_LIST_STRU *notify_list;
    void           (*display)(char *);               /* show the bean content to user */
    unsigned  int   bean_type;
    unsigned  int   bean_size;                       /* bean size*/
    unsigned  int   bean_pos;                        /* the pos of the bean in the bean_process array  */
    char           *bean;                            /* point to the message bean */
} BEAN_PROCESS_STRU;


/* to define the bean_type */
typedef enum BEAN_TYPE
{
    BEAN_LEVEL_0 = 0,
    BEAN_LEVEL_1
}BEAN_TYPE_ENUM;


/*just the only bean level 0 will be register in this array */
typedef struct BEAN_ARRAY
{
    BEAN_PROCESS_STRU    *process;
    char                 flag;
} BEAN_ARRAY_STRU;

typedef struct MSG_HEAD
{
    MODULE_NAME_ENUM moduleid;
    unsigned int     index;
    char             bean[0];
} MSG_HEAD_STRU;



/* name: the name of bean
   data_own: mean the pointe point to the own bean buffer
   data_other: mean the buffer which receive the message from other
                module
*/

#define BEAN_UPDATE_UP(name, bean_local)\
     int update_from_local_##name(char* bean_local)

#define BEAN_UPDATE_DOWN(name, bean_local, bean_receive)\
     int update_to_local_##name(char* bean_local, char* bean_receive)

#define BEAN_CHECK(name, bean_local)\
     int check_para_##name(char* bean_local)

#define BEAN_INIT(name, bean_local)\
     int init_bean_##name(char* bean_local)

#define BEAN_DISPLAY(name, bean_local)\
    void display_##name(char* bean_local)

#define BEAN_NOTIFY(name, beanself, beanbaseon)\
    int notify_##name(char* beanself, char *beanbaseon)

#define STRING(x) #x

#define BEAN_HEAD(name)\
   extern  BEAN_UPDATE_UP(name, bean_local);\
   extern  BEAN_UPDATE_DOWN(name, bean_local,bean_receive);\
   extern  BEAN_CHECK(name, bean_local);\
   extern  BEAN_INIT(name, bean_local);\
   extern  BEAN_DISPLAY(name, bean_local);\


/* if the bean just only update by user or hardware, use this macro to
   define 
*/
#define BEAN_1L_DEF(name, index, type)\
         BEAN_HEAD(name)\
	     static type bean_##name;\
         BEAN_PROCESS_STRU process_##name = { STRING(name),\
                                              update_from_local_##name,\
                                              update_to_local_##name,\
                                              check_para_##name,\
                                              init_bean_##name,\
                                              NULL,\
                                              display_##name,\
                                              BEAN_LEVEL_0,\
                                              sizeof(type),\
                                              index,\
                                              (char*)&bean_##name\
                                              }


/* if the bean update by other bean, use this macro to define */
#define BEAN_2L_DEF(name, type)\
         BEAN_HEAD(name)\
	     static type bean_##name;\
         BEAN_PROCESS_STRU process_##name = { STRING(name),\
                                              NULL,\
                                              NULL,\
                                              NULL,\
                                              init_bean_##name,\
                                              NULL,\
                                              display_##name,\
                                              BEAN_LEVEL_1,\
                                              sizeof(type),\
                                              0xffffffff,\ 
                                              (char*)&bean_##name\
                                              }



#define BEAN_POINTER(name, p)\
    do\
    {\
        extern BEAN_PROCESS_STRU process_##name;\
        bean_get_pointer((BEAN_PROCESS_STRU *)&process_##name, &p);\
    }while(0)


/* */
#define BEAN_BASE_ON(beanself, beanbaseon, notify)\
        do\
        {\
            extern BEAN_PROCESS_STRU process_##beanself;\
            extern BEAN_PROCESS_STRU process_##beanbaseon;\
            bean_base_on(&process##beanself, process_##beanbaseon, notify, STRING(notify));\
        }while(0)



/* regsiter the bean to the bean_process array to update by eagine */
#define BEAN_REGISTER(name)\
    do\
    {\
       extern BEAN_PROCESS_STRU process_##name;\
       bean_register_to_array((BEAN_PROCESS_STRU *)&process_##name);\
    }while(0)

/* this macro should be away used in the bean UPDATE_UP function, when
    any changed for the bean we need informed the msg_process
    to send the bean to other module
 */
#define BEAN_UP_NOTIFY(name)\
    do\
    {\
      extern BEAN_PROCESS_STRU process_##name;\
      bean_update_to_out((BEAN_PROCESS_STRU *)&process_##name);\
      bean_update_notify_list((BEAN_PROCESS_STRU *)&process_##name);\
    }while(0)



#define BEAN_DOWN_NOTIFY(name) \
    do\
    {\
      extern BEAN_PROCESS_STRU process_##name;\
      bean_update_notify_list((BEAN_PROCESS_STRU *)&process_##name);\
    }while(0)


extern BEAN_ARRAY_STRU bean_array[INDEX_BEAN_ALL];
extern MODULE_INFO_STRU module_info;
extern unsigned char module_sync_info[MODULE_MAX];
extern int bean_array_init();
extern void bean_process_run();
extern void bean_base_on(BEAN_PROCESS_STRU *p1, BEAN_PROCESS_STRU *p2, notify func, char *name);
extern int  bean_register_to_array(BEAN_PROCESS_STRU *head);
extern void bean_update_notify_list(BEAN_PROCESS_STRU *bean_process);
extern int bean_update_to_local(char *bean_msg);
extern int bean_update_to_out(BEAN_PROCESS_STRU *bean_process);
extern void bean_get_pointer(BEAN_PROCESS_STRU *process, char **p);
#endif /* __MSG_PROCESS_H__ */
