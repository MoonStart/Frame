#include "common.h"

BEAN_UPDATE_UP(bean_sync, bean_local)
{
    char buffer[MSG_LEN_MAX];
    MODULE_BEAN_STRU *pbean_local = (MODULE_BEAN_STRU *)bean_local;
    MODULE_BEAN_STRU *pbean_send = (MODULE_BEAN_STRU *)buffer; /* the bean will be send */
    int len_save = 0;
    char *ptemp = NULL;
    int   len = 0;
    static int index = 0;
    
    if(!module_sync_info[index] && (index != module_info.ModuleId))
    {
       pbean_local->bean_sync_action = SYNC_BEAN_RESET;
       pbean_local->des_moduleid = index;
       pbean_local->src_moduleid = module_info.ModuleId;
       pbean_local->bean_sync_index = INDEX_BEAN_ALL;
       BEAN_UP_NOTIFY(bean_sync);
    }

    if(pbean_local->bean_sync_action == SYNC_BEAN_FIN)
    {

    }
    else if(pbean_local->bean_sync_action == SYNC_BEAN_RES)
    {
         /* the index of 0 is aways as the module bean */
       ptemp = bean_array[INDEX_BEAN_0].process->bean;
       len_save = bean_array[INDEX_BEAN_0].process->bean_size;

       len = sizeof(MODULE_BEAN_STRU) + bean_array[pbean_local->bean_sync_index].process->bean_size;

        memcpy(pbean_send, pbean_local, sizeof(MODULE_BEAN_STRU));
        memcpy(pbean_send->bean,
               bean_array[pbean_local->bean_sync_index].process->bean,
               bean_array[pbean_local->bean_sync_index].process->bean_size);

        /* now we use the new bean pointer and length to instead the
           bean we have register it
        */
        bean_array[INDEX_BEAN_0].process->bean = (char *)pbean_send;
        bean_array[INDEX_BEAN_0].process->bean_size = len;
        BEAN_UP_NOTIFY(bean_sync);
        bean_array[INDEX_BEAN_0].process->bean = (char *)ptemp;
        bean_array[INDEX_BEAN_0].process->bean_size = len_save;
       
    }
    index ++;
    index %= MODULE_MAX;
    return 0;
}

BEAN_UPDATE_DOWN(bean_sync, bean_local, bean_receive)
{
    MODULE_BEAN_STRU *pbean_local = (MODULE_BEAN_STRU *)bean_local;
    MODULE_BEAN_STRU *pbean_recv =  (MODULE_BEAN_STRU *)bean_receive;
  
    /* the bean request should be register in the array */
    if((pbean_recv->bean_sync_index > INDEX_BEAN_ALL ) || !bean_array[pbean_recv->bean_sync_index].flag)
    {
        return -1;
    }


    /* any bean request from other module */
    if(pbean_recv->bean_sync_action == SYNC_BEAN_REQ)
    {
        /* now we need prepare the respose bean */
        pbean_local->bean_sync_action = SYNC_BEAN_RES;
        pbean_local->bean_sync_index = pbean_recv->bean_sync_index;
        pbean_local->des_moduleid =  pbean_recv->src_moduleid;
        pbean_local->src_moduleid = module_info.ModuleId;
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