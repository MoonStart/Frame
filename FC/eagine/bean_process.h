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
    int            (*run)(char *);     /* use this fun update the bean(typically the hardware changed */
    int            (*update)(char * /* local bean*/, char * /* received bean*/); /* 1st.local bean 2se.received bean. when reive the update message, use this fun to update to lower layer*/
    int            (*check_para)(char *);            /* check any value in this bean rightor not */
    int            (*init_bean)(char *);             /* init the bean function */
    NOTIFY_LIST_STRU *notify_list;
    void           (*display)(char *);               /* show the bean content to user */
    unsigned  int   bean_type;
    unsigned  int   bean_size;                      /* bean size*/
    unsigned  int   des_pos;                        /* the pos of the bean in the scm module bean_process array  */
    unsigned  int   bean_id;                        /* the pos in local array pos */
    char           *bean;                           /* point to the message bean */
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
    CARD_INFO_STRU   card;
    char             bean[0];
}MSG_HEAD_STRU;



/* name: the name of bean
   data_own: mean the pointe point to the own bean buffer
   data_other: mean the buffer which receive the message from other
                module
*/

#define bean_run(n1, n2)\
     int run_local_##n1(char* n2)

#define bean_update(n1, n2, n3)\
     int update_to_local_##n1(char* n2, char* n3)

#define bean_check(n1, n2)\
     int check_para_##n1(char* n2)

#define bean_init(n1, n2)\
     int init_bean_##n1(char* n2)

#define bean_display(n1, n2)\
    void display_##n1(char* n2)

#define bean_notify(n1, n2, n3, n4)\
    int n2##_notify_##n1(void* n3, void *n4)

#define BEAN_HEAD(name)\
   extern  bean_run(name, bean_local);\
   extern  bean_update(name, bean_local,bean_receive);\
   extern  bean_check(name, bean_local);\
   extern  bean_init(name, bean_local);\
   extern  bean_display(name, bean_local);\


/* if the bean just only update by user or hardware, use this macro to
   define 
*/
#define bean_1l_def(name, type)\
         BEAN_HEAD(name)\
	     static type bean_##name;\
         BEAN_PROCESS_STRU process_##name = { STRING(name),\
                                              run_local_##name,\
                                              update_to_local_##name,\
                                              check_para_##name,\
                                              init_bean_##name,\
                                              NULL,\
                                              display_##name,\
                                              BEAN_LEVEL_0,\
                                              sizeof(type),\
                                              0xFFFFFFFF,\
                                              0xFFFFFFFF,\
                                              (char*)&bean_##name\
                                              }


/* if the bean update by other bean, use this macro to define */
#define bean_2l_def(name, type)\
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
                                              0xFFFFFFFF,\
                                              0xFFFFFFFF,\
                                              (char*)&bean_##name\
                                              }



#define bean_pointer(name, p)\
    do\
    {\
        extern BEAN_PROCESS_STRU process_##name;\
        bean_get_pointer((BEAN_PROCESS_STRU *)&process_##name, &p);\
    }while(0)


/* */
#define bean_base_on(n1, n2)\
        do\
        {\
            extern BEAN_PROCESS_STRU process_##n1;\
            extern BEAN_PROCESS_STRU process_##n1;\
            extern int n2##_notify_##n1(void*, void*);\
            bean_base_on(&process_##n1, &process_##n2, n2##_notify_##n1, STRING(n2##_notify_##n1));\
        }while(0)



/* regsiter the bean to the bean_process array to update by eagine */
#define bean_register(name)\
    do\
    {\
       extern BEAN_PROCESS_STRU process_##name;\
       bean_register_to_array((BEAN_PROCESS_STRU *)&process_##name);\
    }while(0)

/* this macro should be away used in the bean UPDATE_UP function, when
    any changed for the bean we need informed the msg_process
    to send the bean to other module
 */
#define bean_sync(name)\
    do\
    {\
      extern BEAN_PROCESS_STRU process_##name;\
      bean_update_to_out((BEAN_PROCESS_STRU *)&process_##name);\
      bean_update_notify_list((BEAN_PROCESS_STRU *)&process_##name);\
    }while(0)



extern BEAN_ARRAY_STRU bean_array[BEAN_ARRAY_SIZE];
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
