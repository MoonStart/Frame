/******************************************************************************

  Copyright (C), 2001-2011, DCN Co., Ltd.

 ******************************************************************************
  File Name     : io_process.h
  Version       : Initial Draft
  Author        : Eason Lee
  Created       : 2014/9/12
  Last Modified :
  Description   : io_process.c header file
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

#ifndef __IO_PROCESS_H__
#define __IO_PROCESS_H__
#include "common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

extern int display();
extern char io_init(MODULE_NAME_ENUM name);
extern int io_recv(char *msg, unsigned short len);
extern int io_send(char *msg, unsigned short len);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __IO_PROCESS_H__ */
