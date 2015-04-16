/******************************************************************************

  Copyright (C), 2001-2011, DCN Co., Ltd.

 ******************************************************************************
  File Name     : card_bean.h
  Version       : Initial Draft
  Author        : Eason Lee
  Created       : 2014/9/12
  Last Modified :
  Description   : card_bean.c header file
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

#ifndef __CARD_BEAN_H__
#define __CARD_BEAN_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/* the struct was the real message used by the module*/
typedef struct CARD_MSG_BEAN
{
  int  x;
  int  y;
  int  z;
}CARD_MSG_BEAN_STRU;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __CARD_BEAN_H__ */
