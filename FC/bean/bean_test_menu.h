/******************************************************************************

  Copyright (C), 2001-2011, DCN Co., Ltd.

 ******************************************************************************
  File Name     : bean_test_menu.h
  Version       : Initial Draft
  Author        : Laserlee
  Created       : 2015/7/2
  Last Modified :
  Description   : bean_test_menu.c header file
  Function List :
  History       :
  1.Date        : 2015/7/2
    Author      : Laserlee
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

#ifndef __BEAN_TEST_MENU_H__
#define __BEAN_TEST_MENU_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

typedef struct BUG_LOCK
{
    bool bean_callstack;             
}BUG_LOCK_STRU;

extern BUG_LOCK_STRU bug_instance;
extern void bean_test_menu_register();

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __BEAN_TEST_MENU_H__ */
