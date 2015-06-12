#include "common.h"
/* the bean 0 need't to be sync so we set index start with 1 */
static int bean_sync_count = 1;


BEAN_UPDATE_UP(bean_sync, bean_local)
{
    MODULE_BEAN_STRU *pbean_local = (MODULE_BEAN_STRU *)bean_local;
    static unsigned int index = INDEX_BEAN_1; /* becareful */

    if(module_sync_info[module_info.ModuleId])
    {
       return 0;
    }
    else if(pbean_local->bean_sync_action == SYNC_BEAN_FIN )
    {
        BEAN_UP_NOTIFY(bean_sync);
        module_sync_info[module_info.ModuleId] = true;
        printf("the module %d sync have been finished \r\n", module_info.ModuleId);
        return 0;
    }

    if((index != INDEX_BEAN_0) && bean_array[index].flag)
    {
        pbean_local->src_moduleid = module_info.ModuleId;
        pbean_local->bean_sync_index = index;
        pbean_local->bean_sync_action = SYNC_BEAN_REQ;
        BEAN_UP_NOTIFY(bean_sync);
    }
    index ++;
    index = index % INDEX_BEAN_ALL;
    return 0;
}



BEAN_UPDATE_DOWN(bean_sync, bean_local, bean_receive)
{
    MODULE_BEAN_STRU *pbean_local = (MODULE_BEAN_STRU *)bean_local;
    MODULE_BEAN_STRU *pbean_recv =  (MODULE_BEAN_STRU *)bean_receive;
    MODULE_BEAN_STRU *pbean_send = NULL; /* the bean will be send */

    BEAN_PROCESS_STRU *process_temp = NULL; /* for bean_sync */

    /* the bean request should be register in the array */
    if((pbean_recv->bean_sync_index > INDEX_BEAN_ALL ) || 
        !bean_array[pbean_recv->bean_sync_index].flag)
    {
        return -1;
    }

    /* any bean request from other module */
    if(pbean_recv->bean_sync_action == SYNC_BEAN_RESET)
    {
       printf("the module sync info need to reset \r\n");
       module_sync_info[module_info.ModuleId] = false;
       pbean_local->des_moduleid = pbean_local->src_moduleid;
       pbean_local->src_moduleid = module_info.ModuleId;
       pbean_local->bean_sync_action = SYNC_BEAN_RESET;
       bean_sync_count = 1;
    }
    else if(pbean_recv->bean_sync_action == SYNC_BEAN_REQ)
    {
        return -1;
    }
    else if(pbean_recv->bean_sync_action == SYNC_BEAN_RES)
    {
        process_temp = bean_array[pbean_recv->bean_sync_index].process;
        process_temp->update_to_local(process_temp->bean, pbean_recv->bean);
        bean_sync_count ++;
        if(bean_sync_count == module_info.bean_count)
        {
           pbean_local->bean_sync_action = SYNC_BEAN_FIN;
           pbean_local->bean_sync_index = INDEX_BEAN_ALL;
        }
        pbean_local->des_moduleid = pbean_recv->src_moduleid;
        pbean_local->src_moduleid = module_info.ModuleId;
        return 0;
    }
    else if(pbean_recv->bean_sync_action == SYNC_BEAN_FIN)
    {
        return -1;
    }

    return 0;
}