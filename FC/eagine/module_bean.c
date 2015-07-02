#include "common.h"

BEAN_1L_DEF(SYS_BEAN_SYNC, INDEX_BEAN_0, MODULE_BEAN_STRU);


BEAN_INIT(SYS_BEAN_SYNC, bean_local)
{
    memset(bean_local, 0x00, sizeof(MODULE_BEAN_STRU));
    return 0;
}

BEAN_DISPLAY(SYS_BEAN_SYNC, bean_local)
{
    MODULE_BEAN_STRU *p = (MODULE_BEAN_STRU *)bean_local;
    int index = 0;
    while(index < MODULE_MAX)
    {
      printf("\tmodule_sync_info[ %s ] = %s\r\n",STR_MODULE_NAME(index), ((module_sync_info[index]==1)?"true":"false"));
      index ++;
    }
    printf("\tmoduleid_local = %s\r\n", STR_MODULE_NAME(module_info.ModuleId));
    printf("\tbean_sync_action = %s\r\n", STR_BEAN_SYNC_ACTION(p->bean_sync_action));
    printf("\tbean_index = %d\r\n", p->bean_sync_index);
}

BEAN_CHECK(SYS_BEAN_SYNC, bean_local)
{
    return 0;
}




