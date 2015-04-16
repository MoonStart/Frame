#include "common.h"


void card_main()
{
   /**/
   io_init(MODULE_CARD);

   msg_array_init();

   {REGISTER_MSG(card_bean);}
}

pfunc module_main = card_main;