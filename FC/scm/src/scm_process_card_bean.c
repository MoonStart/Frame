#include "common.h"

MSG_SYNC(card_bean, data_own)
{
  CARD_MSG_BEAN_STRU *p = NULL;
  if(data_own == NULL)
    return -1;

  p = (CARD_MSG_BEAN_STRU *)data_own;

  PRINTF("x=%d y=%d z=%d \r\n", p->x, p->y, p->z);
  p->x = 13;
  
  PRINTF("%s %d \r\n", __FILE__, __LINE__);

  if (1/*anychanged*/)
  {
     SYNC_MSG(card_bean);
  }
  
  return 0;
}


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

