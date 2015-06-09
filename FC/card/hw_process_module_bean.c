#include "common.h"
static int bean_sync_count = 0;


BEAN_UPDATE_UP(bean_sync, bean_local)
{
    MODULE_BEAN_STRU *pbean_local = (MODULE_BEAN_STRU *)bean_local;
    static unsigned int index = INDEX_BEAN_1; /* becareful */

    pbean_local->module_id = module_info.ModuleId;

    /* if have been do sync, just return do nothing
       first bean need't been sync
    */
    if(module_sync[module_info.ModuleId])
    {
        return 0;
    }
    else if(module_info.bean_count == (bean_sync_count + 1))
    {
        pbean_local->bean_sync_action = SYNC_BEAN_FIN;
        pbean_local->bean_index = INDEX_BEAN_0;
        BEAN_UPDATE_NOTIFY(bean_sync);
        module_sync[module_info.ModuleId] = true;
        printf("the module %d sync have been finished \r\n", module_info.ModuleId);
        return 0;
    }

    if((index != INDEX_BEAN_0) && (index != INDEX_BEAN_MAX) && bean_array[index].flag)
    {
        pbean_local->bean_index = index;
        pbean_local->bean_sync_action = SYNC_BEAN_REQ;
        BEAN_UPDATE_NOTIFY(bean_sync);
    }
    index ++;
    index = index % INDEX_BEAN_MAX;
    return 0;
}



BEAN_UPDATE_DOWN(bean_sync, bean_local, bean_receive)
{
    MODULE_BEAN_STRU *pbean_local = (MODULE_BEAN_STRU *)bean_local;
    MODULE_BEAN_STRU *pbean_recv =  (MODULE_BEAN_STRU *)bean_receive;
    MODULE_BEAN_STRU *pbean_send = NULL; /* the bean will be send */

    BEAN_PROCESS_STRU *process_temp = NULL; /* for bean_sync */

    if(module_info.bean_count == (bean_sync_count + 1))
        return 0;

    /* the bean request should be register in the array */
    if((pbean_recv->bean_index > INDEX_BEAN_MAX ) || !bean_array[pbean_recv->bean_index].flag)
    {
        return -1;
    }

    /* any bean request from other module */
    if(pbean_recv->bean_sync_action == SYNC_BEAN_REQ)
    {
        return -1;
    }
    else if(pbean_recv->bean_sync_action == SYNC_BEAN_RES)
    {
        process_temp = bean_array[pbean_recv->bean_index].process;
        process_temp->update_to_local(process_temp->bean, pbean_recv->bean);
        bean_sync_count++;
        return 0;
    }
    else if(pbean_recv->bean_sync_action == SYNC_BEAN_FIN)
    {
        return -1;
    }

    return 0;
}