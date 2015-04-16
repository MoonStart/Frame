#include "common.h"

/* we need */
MSG_PROCESS(card_bean, "CardMsgBean", ID_MSG_CARD, CARD_MSG_BEAN_STRU);


MSG_CHECK(card_bean, data)
{
  CARD_MSG_BEAN_STRU *p = NULL;
  if(data == NULL)
    return -1;


  p = (CARD_MSG_BEAN_STRU *)data;

  if(p->x > 100)
  {
    PRINTF("the value x is error \r\n");
  }

 
  PRINTF("%s %d \r\n", __FILE__, __LINE__);
  return 0;
}


MSG_INIT(card_bean, data)
{
  CARD_MSG_BEAN_STRU *p = NULL;
  if(data == NULL)
    return -1;
  
   p = (CARD_MSG_BEAN_STRU *)data;


   p->x = 10;
   p->y = 12;
   p->z = 13;

   PRINTF("card bean init over \r\n");
   return 0;
}