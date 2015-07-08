#include "common.h"

BEAN_RUN(SYS_BEAN_SYNC, bean_local)
{
    MODULE_BEAN_STRU *pbean_local = (MODULE_BEAN_STRU *)bean_local;
    static int index = 0;
    
    if(!module_sync_info[index] && (index != module_info.ModuleId))
    {
       pbean_local->bean_sync_action = SYNC_BEAN_RESET;
       pbean_local->des_moduleid = index;
       pbean_local->src_moduleid = module_info.ModuleId;
       pbean_local->bean_sync_index = 0xFFFFFFFF;
       BEAN_SYNC(SYS_BEAN_SYNC);
    }

    index ++;
    index %= MODULE_MAX;
    return 0;
}

BEAN_UPDATE(SYS_BEAN_SYNC, bean_local, bean_receive)
{
    MODULE_BEAN_STRU *pbean_local = (MODULE_BEAN_STRU *)bean_local;
    MODULE_BEAN_STRU *pbean_recv =  (MODULE_BEAN_STRU *)bean_receive;
    MODULE_BEAN_STRU *pbean_send = (MODULE_BEAN_STRU *)buffer; 

    char buffer[MSG_LEN_MAX];
      /* the bean will be send */
    int  len_save   = 0;
    char *ptemp     = NULL;
    int  len        = 0;
    
    /* any bean request from other module */
    if(pbean_recv->bean_sync_action == SYNC_BEAN_REQ)
    {
        /* now we need prepare the respose bean */
        pbean_local->bean_sync_action = SYNC_BEAN_RES;
        pbean_local->bean_sync_index = pbean_recv->bean_sync_index;
        pbean_local->des_moduleid =  pbean_recv->src_moduleid;
        pbean_local->src_moduleid = module_info.ModuleId;

          /* the index of 0 is aways as the module bean */
       ptemp = bean_array[0].process->bean;
       len_save = bean_array[0].process->bean_size;

       len = sizeof(MODULE_BEAN_STRU) + bean_array[pbean_local->bean_sync_index].process->bean_size;

        memcpy(pbean_send, pbean_local, sizeof(MODULE_BEAN_STRU));
        memcpy(pbean_send->bean,
               bean_array[pbean_local->bean_sync_index].process->bean,
               bean_array[pbean_local->bean_sync_index].process->bean_size);

        /* now we use the new bean pointer and length to instead the
           bean we have register it
        */
        bean_array[0].process->bean = (char *)pbean_send;
        bean_array[0].process->bean_size = len;
        BEAN_SYNC(SYS_BEAN_SYNC);
        bean_array[0].process->bean = (char *)ptemp;
        bean_array[0].process->bean_size = len_save;
    }
    else if(pbean_recv->bean_sync_action == SYNC_BEAN_RES)
    {
        return -1;
    }
    else if(pbean_recv->bean_sync_action == SYNC_BEAN_FIN && pbean_recv->bean_sync_index == INDEX_BEAN_ALL)
    {
        /* when the pos of module sync as true, we use the bean from
           other module to update the bean of SCM
        */
        module_sync_info[pbean_recv->src_moduleid] = true;
        pbean_local->bean_sync_action = SYNC_BEAN_RESET;
    }

    return 0;
}