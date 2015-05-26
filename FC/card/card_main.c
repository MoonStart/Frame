#include "common.h"


void card_main()
{

   {INIT_LIST(CARD1, MODULE_CARD);}
   printf("init function over! \r\n");

   {REGISTER_MSG(card_bean);}
   printf("message bean register over! \r\n");
}

pfunc module_main = card_main;