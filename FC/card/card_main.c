#include "common.h"


void card_main()
{
    {INIT_LIST(CARD1, MODULE_CARD);}

    {BEAN_REGISTER(SYS_BEAN_SYNC);}
    {BEAN_REGISTER(EDFA);}
}

pfunc module_main = card_main;