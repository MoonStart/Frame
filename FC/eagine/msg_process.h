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

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


#define MSG_LEN_MAX       256


typedef enum ACTION
{
    EN_ACTION_NOCHANGE=0,
    EN_ACTION_SYNC
}ACTION_ENUM;//0:do nothing 1:send the buffer to another module


typedef struct MSG_PROCESS
{
    char           *name;                            /* the string which show to user what is the name of this bean*/
    char            action;                          //use the ACTION_SYNC enum define 
    int            (*update_from_local)(char*);      //use this fun update the bean(typically the hardware changed )
    int            (*update_to_local)(char*, char*); //when recive the update message, use this fun to update to lower layer
    int            (*check_para)(char*);             //check any value in this bean rightor not
    int            (*init_bean)(char*);
    unsigned  int   bean_size;                       /* buffer len*/
    unsigned  int   bean_pos;                        /* the pos in the message array, not a good way  */
    char*           bean;                            /* point to the message bean */
}MSG_PROCESS_STRU; 

/* name: the name of bean
   data_own: mean the pointe point to the own bean buffer
   data_other: mean the buffer which receive the message from other
                module
*/

#define MSG_SYNC(name, data_own) \ 
     int update_from_local_##name(char* data_own)

#define MSG_SET(name, data_own, data_other) \
     int update_to_local_##name(char* data_own, char* data_other)

#define MSG_CHECK(name, data_own) \
     char check_para_##name(char* data_own)

#define MSG_INIT(name, data_own) \
     char init_bean_##name(char* data_own)

#define MSG_PROCESS(name, strname, index, type) \
   extern  MSG_SYNC(name, data_own); \
   extern  MSG_SET(name, data_own, data_other); \
    MSG_CHECK(name, data_own); \ 
    MSG_INIT(name, data_own); \
    static type bean_##name ; \
         MSG_PROCESS_STRU process_##name = {strname, \
                                              EN_ACTION_NOCHANGE,\
                                              update_from_local_##name,\
                                              update_to_local_##name,\
                                              check_para_##name, \
                                              init_bean_##name, \
                                              sizeof(type), \
                                              index, \
                                              &bean_##name \
                                              }

#define POINTER_BEAN(name) &bean_##name


#define REGISTER_MSG(name) \
    do \
    { \
       extern MSG_PROCESS_STRU process_##name; \
       register_to_msg_array((MSG_PROCESS_STRU *)&process_##name); \
    }while(0)

/* this macro should be away used in the bean get function, when 
    any changed for the bean we need informed the msg_process 
    to send the bean to other module 
 */
#define SYNC_MSG(name) \
    do \
    { \
      extern MSG_PROCESS_STRU process_##name; \
      process_##name.action = EN_ACTION_SYNC; \
    }while(0)

extern int msg_array_init();
extern int msg_process(char* msg);
extern void process_run();
extern int register_to_msg_array(MSG_PROCESS_STRU *head);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __MSG_PROCESS_H__ */
