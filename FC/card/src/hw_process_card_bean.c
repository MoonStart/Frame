#include "common.h"

/* send the message bean to other module */
MSG_SYNC(card_bean, data)
{
  CARD_MSG_BEAN_STRU *p = NULL;
  if(data == NULL)
    return -1;

  p = (CARD_MSG_BEAN_STRU *)data;

  /* any changed action*/
  SYNC_MSG(card_bean)
  PRINTF("%s %d \r\n", __FILE__, __LINE__);
  return -1;
}


MSG_SET(card_bean, data)
{
  CARD_MSG_BEAN_STRU *p = NULL;
  if(data == NULL)
    return -1;

  p = (CARD_MSG_BEAN_STRU *)data;
  if(p->x ^ )
  PRINTF("x=%d y=%d z=%d \r\n", p->x, p->y, p->z);
  PRINTF("%s %d \r\n", __FILE__, __LINE__);
  return 0;

}
