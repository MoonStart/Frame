#include "common.h"

/* send the message bean to other module */
MSG_SYNC(card_bean, data_own)
{
  CARD_MSG_BEAN_STRU *p = NULL;
  if(data_own == NULL)
    return -1;

  p = (CARD_MSG_BEAN_STRU *)data_own;

  /* any changed action*/
 // SYNC_MSG(card_bean);
  PRINTF("%s %d \r\n", __FILE__, __LINE__);
  return -1;
}

/*****************************************************************************
 Prototype    : MSG_SET
 Description  : typical use example, when received from other message
                 ,update the local message bean
 Input        : card_bean   
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
MSG_SET(card_bean, data_own, data_other)
{
  CARD_MSG_BEAN_STRU *pown = NULL;
  CARD_MSG_BEAN_STRU *pother = NULL;

  if(data_own == NULL || data_other == NULL)
    return -1;

  pown = (CARD_MSG_BEAN_STRU *)data_own;
  pother = (CARD_MSG_BEAN_STRU *)data_other;

  if(pown->x ^ pother->x)
  {
    //do anything
    pown->x = pother->x;
  }

  //just the same action to other fields 
  
  PRINTF("%s %d \r\n", __FILE__, __LINE__);
  return 0;
}