#include "common.h"

/*****************************************************************************
 �� �� ��  : BEAN_UPDATE_UP
 ��������  : update the bean from local hw or other reson and should
             send the new bean to other module
 �������  : EDFA
             data_own
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : Thursday, May 28, 2015
    ��    ��   : name
    �޸�����   : �����ɺ���

*****************************************************************************/
BEAN_UPDATE_UP(EDFA, bean_local)
{
    CARD_MSG_BEAN_STRU *p = (CARD_MSG_BEAN_STRU *)bean_local;


    return -1;
}

/*****************************************************************************
 Prototype    : MSG_SET
 Description  : typical use example, when received from other message
                 ,update the local message bean
 Input        : EDFA
                data_own
                data_other
 Output       : None
 Return Value :
 Calls        :
 Called By    :

  History        :
  1.Date         : 2015/4/16
    Author       : Laserly
    Modification : Created function

*****************************************************************************/
BEAN_UPDATE_DOWN(EDFA, bean_local, bean_receive)
{
    CARD_MSG_BEAN_STRU *plocal = NULL;
    CARD_MSG_BEAN_STRU *pother = NULL;

    if(bean_local == NULL || bean_receive == NULL)
        return -1;

    plocal = (CARD_MSG_BEAN_STRU *)bean_local;
    pother = (CARD_MSG_BEAN_STRU *)bean_receive;

    if(plocal->x ^ pother->x)
    {
        printf("old:%d new:%d \r\n", plocal->x, pother->x);
        plocal->x = pother->x;
    }
    return 0;
}