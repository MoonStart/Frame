#include "common.h"

/* define a bean which need to be process by the eagine  */
BEAN_DEFINE(EDFA, INDEX_BEAN_1, CARD_MSG_BEAN_STRU);


BEAN_CHECK(EDFA, bean_local)
{
  CARD_MSG_BEAN_STRU *p = (CARD_MSG_BEAN_STRU *)bean_local;

  if(p->x > 100)
  {
    PRINTF("the value x is error \r\n");
  }
  return 0;
}

BEAN_DISPLAY(EDFA, bean_local)
{
  CARD_MSG_BEAN_STRU *p = (CARD_MSG_BEAN_STRU *)bean_local;
   printf("\tX:%d\r\n", p->x);
   printf("\tY:%d\r\n", p->y);
   printf("\tZ:%d\r\n", p->z);
}

static void setcardbean(int argc, char** argv)
{
   char *p = NULL;
   CARD_MSG_BEAN_STRU *plocal = NULL;
  
   BEAN_POINTER(EDFA, p);
   plocal = (CARD_MSG_BEAN_STRU *)p;
   if(argc != 4)
   {
     printf("command format: card set [x|y|z] value(int) \r\n");
     return;
   }

   if(strcmp(argv[2], "x") == 0)
   {
     plocal->x = atoi(argv[3]); 
     BEAN_UPDATE_NOTIFY(EDFA);
   }
}

static CMD_TABLE_STRU cardMenu[] =
{   // cmd   sub_cmd_name               cmd_help                sub_cmd_help             fct_call        fct_call2
    {"BeanSet",   STRING(EDFA),    "-Set the Bean content", "-the Name of the Bean would be changed ",             setcardbean,     NULL}
};


BEAN_INIT(EDFA, bean_local)
{
  CARD_MSG_BEAN_STRU *p = (CARD_MSG_BEAN_STRU *)bean_local;

  RegisterCommand(cardMenu, sizeof(cardMenu)/sizeof(CMD_TABLE_STRU));
  printf("bean init over \r\n");
  return 0;
}