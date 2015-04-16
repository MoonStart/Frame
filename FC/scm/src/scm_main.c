#include "common.h"


void scm_main()
{
   /* call all module init function at here */

   io_init(MODULE_SCM);

   msg_array_init();

   {REGISTER_MSG(card_bean);}
}

pfunc module_main = scm_main;