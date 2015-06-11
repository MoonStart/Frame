#include "common.h"

/*****************************************************************************
 Prototype    : BEAN_UPDATE_UP
 Description  : for SCM module, the bean just only update by user to up
                direction, we treat the user as same as the hw, that is much more
                easy to understand 
 Input        : EDFA        
                bean_local  
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2015/6/11
    Author       : Laserlee
    Modification : Created function

*****************************************************************************/
BEAN_UPDATE_UP(EDFA, bean_local)
{
    CARD_MSG_BEAN_STRU *p = (CARD_MSG_BEAN_STRU *)bean_local;
    if(p == NULL)
        return -1;

    return 0;
}


BEAN_UPDATE_DOWN(EDFA, bean_local, bean_receive)
{
    CARD_MSG_BEAN_STRU *plocal = NULL;
    CARD_MSG_BEAN_STRU *pother = NULL;

    if(bean_local == NULL || bean_receive == NULL)
        return -1;

    plocal =  (CARD_MSG_BEAN_STRU *)bean_local;
    pother = (CARD_MSG_BEAN_STRU *)bean_receive;

    if(plocal->x ^ pother->x)
    {
        printf("old:%d new:%d \r\n", plocal->x, pother->x);
        plocal->x = pother->x;
    }
    return 0;
}

