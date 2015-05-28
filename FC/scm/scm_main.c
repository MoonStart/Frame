#include "common.h"

void scm_main()
{
   {INIT_LIST(SCM, MODULE_SCM);}
   printf("init function over! \r\n");
   
   {BEAN_REGISTER(card_bean);}
   printf("message bean register over! \r\n");
   
}

pfunc module_main = scm_main;