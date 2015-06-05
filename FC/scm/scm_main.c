#include "common.h"

void scm_main()
{
    {
        INIT_LIST(SCM, MODULE_SCM);
    }
    printf("init function over! \r\n");


    /* every module should register bean_sync */
    {
        BEAN_REGISTER(bean_sync);
    }
    {
        BEAN_REGISTER(EDFA);
    }
    printf("message bean register over! \r\n");

}

pfunc module_main = scm_main;