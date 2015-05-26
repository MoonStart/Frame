#include "common.h"


void card_main()
{

   {INIT_LIST(CARD1, MODULE_CARD);}

   {REGISTER_MSG(card_bean);}
}

pfunc module_main = card_main;