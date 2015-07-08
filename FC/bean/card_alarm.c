#include "common.h"

BEAN_2L_DEF(EDFA_AM, CARD_AL_STRU);

BEAN_INIT(EDFA_AM, bean_local)
{
   BEAN_BASE_ON(EDFA_AM, EDFA);
}


BEAN_DISPLAY(EDFA_AM, bean_local)
{
  printf("alarm:%d \r\n", 1);
}

BEAN_NOTIFY(EDFA_AM, EDFA, beanself, beanbaseon)
{
   printf("have been notify \r\n");
}
