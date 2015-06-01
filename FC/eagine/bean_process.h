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


typedef enum ACTION
{
    EN_ACTION_NOCHANGE=0,
    EN_ACTION_UPDATE_TO_UP, /* any changed occured in local*/
    EN_ACTION_UPDATE_TO_DOWN /* any changed from user or other module */
}ACTION_ENUM;



/* when a bean update, we need notify another module to update the 
corespond bean also */
typedef void  (*notify)(char *);

typedef struct UPDATE_NOTIFY_LIST
{
    notify  pNotify;
    struct UPDATE_NOTIFY_LIST *next;
}UPDATE_NOTIFY_LIST_STRU;

typedef struct BEAN_PROCESS
{
    char           *bean_name;                       /* the string which show to user what is the name of this bean*/
    ACTION_ENUM    action;                           /* use the ACTION_SYNC enum define */
    int            (*update_from_local)(char*);      /* use this fun update the bean(typically the hardware changed */
    int            (*update_to_local)(char* /* local bean*/, char* /* received bean*/); /* 1st.local bean 2se.received bean. when reive the update message, use this fun to update to lower layer*/
    int            (*check_para)(char*);             /* check any value in this bean rightor not */
    int            (*init_bean)(char*);              /* init the bean function */
    void           (*display)(char*);                /* show the bean content to user */
    unsigned  int   bean_size;                       /* bean size*/
    unsigned  int   bean_pos;                        /* the pos of the bean in the bean_process array  */
    UPDATE_NOTIFY_LIST_STRU  *list;                  /* notify list, when the bean update we need notify other module insterseted*/
    char*           bean;                            /* point to the message bean */
}BEAN_PROCESS_STRU; 

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


#define STRING(x) #x

#define BEAN_HEAD(name)\
   extern  BEAN_UPDATE_UP(name, bean_local);\
   extern  BEAN_UPDATE_DOWN(name, bean_local,bean_receive);\
   extern  BEAN_CHECK(name, bean_local);\
   extern  BEAN_INIT(name, bean_local);\
   extern  BEAN_DISPLAY(name, bean_local);\

#define BEAN_DEFINE(name, index, type)\
         BEAN_HEAD(name)\
	     static type bean_##name;\
         BEAN_PROCESS_STRU process_##name = { STRING(name),\
                                              EN_ACTION_NOCHANGE,\
                                              update_from_local_##name,\
                                              update_to_local_##name,\
                                              check_para_##name,\
                                              init_bean_##name,\
                                              display_##name,\
                                              sizeof(type),\
                                              index,\
                                              NULL,\
                                              (char*)&bean_##name\
                                              }

#define BEAN_GET(name) &bean_##name

#define REGISTER_NOTIFY(name,func)\
    do\
    {\
         extern BEAN_PROCESS_STRU process_##name;\
         bean_add_list((BEAN_PROCESS_STRU *)&process_##name, func);\
    }while(0)



/* regsiter the bean to the bean_process array to update by eagine */
#define BEAN_REGISTER(name)\
    do\
    {\
       extern BEAN_PROCESS_STRU process_##name;\
       bean_register_to_array((BEAN_PROCESS_STRU *)&process_##name);\
    }while(0)

/* this macro should be away used in the bean get function, when 
    any changed for the bean we need informed the msg_process 
    to send the bean to other module 
 */
#define BEAN_UPDATE_NOTIFY(name)\
    do\
    {\
      extern BEAN_PROCESS_STRU process_##name;\
      bean_update_notify((BEAN_PROCESS_STRU *)&process_##name);\
    }while(0)

#if 0
#define BEAN_SET_DOWN(name) \
    do\
    {\
      extern BEAN_PROCESS_STRU process_##name;\
      process_##name.action = EN_ACTION_UPDATE_TO_DOWN;\
    }while(0) 
#endif

extern int bean_array_init();
extern void bean_process_run();
extern int  bean_register_to_array(BEAN_PROCESS_STRU *head);
extern void bean_update_notify(BEAN_PROCESS_STRU * bean_process);
extern void bean_add_list(BEAN_PROCESS_STRU * bean_process, notify func);
extern int bean_update(char *msg);

#endif /* __MSG_PROCESS_H__ */
