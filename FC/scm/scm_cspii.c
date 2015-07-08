#include "common.h"
CARD_INFO_STRU card_instance;



CSPII_INIT(SCM, module)
{
    card_instance.shelf = 0;
    card_instance.slot  = 0;
    card_instance.card = module;
    return 0;
}



