#include "common.h"


void card_main()
{

    {
        INIT_LIST(CARD1, MODULE_CARD);
    }
    printf("init function over! \r\n");

    {
        BEAN_REGISTER(bean_sync);
    }
    {
        BEAN_REGISTER(EDFA);
    }
    printf("bean register over! \r\n");
}

pfunc module_main = card_main;