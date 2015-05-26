#include "common.h"

MSG_SYNC(card_bean, data_own)
{
  CARD_MSG_BEAN_STRU *p = NULL;
  if(data_own == NULL)
    return -1;

  p = (CARD_MSG_BEAN_STRU *)data_own;

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
    printf("old:%d new:%d \r\n", pown->x, pother->x);
    pown->x = pother->x;
  }
  return 0;
}

