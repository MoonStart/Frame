#include "common.h"

/* define a bean which need to be process by the eagine  */
BEAN_DEFINE(EDFA, INDEX_BEAN_1, CARD_MSG_BEAN_STRU);


BEAN_CHECK(EDFA, bean_local)
{
    CARD_MSG_BEAN_STRU *p = (CARD_MSG_BEAN_STRU *)bean_local;

    if(p->x > 100)
    {
        PRINTF("the value x is error \r\n");
    }
    return 0;
}

BEAN_DISPLAY(EDFA, bean_local)
{
    CARD_MSG_BEAN_STRU *p = (CARD_MSG_BEAN_STRU *)bean_local;
    printf("\tX:%d\r\n", p->x);
    printf("\tY:%d\r\n", p->y);
    printf("\tZ:%d\r\n", p->z);
}




BEAN_INIT(EDFA, bean_local)
{
    CARD_MSG_BEAN_STRU *p = (CARD_MSG_BEAN_STRU *)bean_local;
    printf("bean init over \r\n");
    return 0;
}