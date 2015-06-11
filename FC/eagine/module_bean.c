#include "common.h"

BEAN_DEFINE(bean_sync, INDEX_BEAN_0, MODULE_BEAN_STRU);


BEAN_INIT(bean_sync, bean_local)
{
    return 0;
}

BEAN_DISPLAY(bean_sync, bean_local)
{
    MODULE_BEAN_STRU *p = (MODULE_BEAN_STRU *)bean_local;

    printf("\tmodule_id=%d\r\n", p->module_id);
    printf("\tbean_sync_action=%s\r\n", STR_BEAN_SYNC_ACTION(p->bean_sync_action));
    printf("\tbean_index=%d\r\n", p->bean_index);
}

BEAN_CHECK(bean_sync, bean_local)
{
    return 0;
}




