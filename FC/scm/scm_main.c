#include "common.h"

void scm_main()
{
    {INIT_LIST(SCM, MODULE_SCM);}
    
    /* every module should register SYS_BEAN_SYNC */
    {BEAN_REGISTER(SYS_BEAN_SYNC);}
    {BEAN_REGISTER(EDFA);}
    {BEAN_REGISTER(EDFA_AM);}
}

pfunc module_main = scm_main;