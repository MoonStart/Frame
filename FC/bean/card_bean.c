#include "common.h"

/* we need */
MSG_PROCESS(card_bean, "card", INDEX_BEAN_1, CARD_MSG_BEAN_STRU);


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
  return 0;
}

static void display(int argc, char** argv)
{
   CARD_MSG_BEAN_STRU *p = POINTER_BEAN(card_bean);
   printf("cardbean value: \r\n");
   printf("x:%d\r\n", p->x);
   printf("x:%d\r\n", p->y);
   printf("x:%d\r\n", p->z);
}

static void setcardbean(int argc, char** argv)
{
   CARD_MSG_BEAN_STRU *p = POINTER_BEAN(card_bean);

   if(argc != 4)
   {
     printf("command format: card set [x|y|z] value(int) \r\n");
     return;
   }

   if(strcmp(argv[2], "x") == 0)
   {
     p->x = atoi(argv[3]); 
     SYNC_MSG(card_bean);
   }
}

#define CMD1 "card"
static CMD_TABLE_STRU cardMenu[] =
{   // cmd   sub_cmd_name   cmd_help    sub_cmd_help             fct_call        fct_call2
    { CMD1, "display",     "card - display the card content",  "display the card  ",      display,         NULL},
    { NULL, "set",         NULL,                               "set the content of card", setcardbean,     NULL}
};


MSG_INIT(card_bean, data)
{
  CARD_MSG_BEAN_STRU *p = NULL;
  if(data == NULL)
    return -1;
  
   p = (CARD_MSG_BEAN_STRU *)data;

   RegisterCommand(cardMenu, sizeof(cardMenu)/sizeof(CMD_TABLE_STRU));
   printf("bean init over \r\n");
   return 0;
}