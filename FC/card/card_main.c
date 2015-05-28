#include "common.h"


void card_main()
{

   {INIT_LIST(CARD1, MODULE_CARD);}
   printf("init function over! \r\n");

   {BEAN_REGISTER(card_bean);}
   printf("bean register over! \r\n");
}

pfunc module_main = card_main;