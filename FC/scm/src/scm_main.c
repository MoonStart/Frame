#include "common.h"


void scm_main()
{

   INIT_LIST(SCM, MODULE_SCM);
   
   {REGISTER_MSG(card_bean);}
}

pfunc module_main = scm_main;