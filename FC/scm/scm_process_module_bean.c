#include "common.h"

BEAN_UPDATE_UP(bean_sync, bean_local)
{
    return 0;
}

BEAN_UPDATE_DOWN(bean_sync, bean_local, bean_receive)
{
    int   len = 0;
    MODULE_BEAN_STRU *pbean_local = NULL;
    MODULE_BEAN_STRU *pbean_recv =  (MODULE_BEAN_STRU *)bean_receive;
    MODULE_BEAN_STRU *pbean_send = NULL; /* the bean will be send */

    int len_save = 0;
    char *ptemp = NULL;

    /* the index of 0 is aways as the module bean */
    ptemp = bean_array[INDEX_BEAN_0].process->bean;
    len_save = bean_array[INDEX_BEAN_0].process->bean_size;


    /* the bean request should be register in the array */
    if((pbean_recv->bean_index > INDEX_BEAN_MAX ) || !bean_array[pbean_recv->bean_index].flag)
    {
        return -1;
    }

    len = sizeof(MODULE_BEAN_STRU) + bean_array[pbean_recv->bean_index].process->bean_size;

    pbean_send = (MODULE_BEAN_STRU *)malloc(len);
    if(pbean_send == NULL)
    {
        return -1;
    }

    /* any bean request from other module */
    if(pbean_recv->bean_sync_action == SYNC_BEAN_REQ)
    {
        /* now we need prepare the respose bean */
        pbean_send->bean_sync_action = SYNC_BEAN_RES;
        pbean_send->bean_index = pbean_recv->bean_index;
        pbean_send->module_id =  pbean_recv->module_id;

        /* now we copy the local bean content to the bean_send */
        memcpy(pbean_send->bean,
               bean_array[pbean_recv->bean_index].process->bean,
               bean_array[pbean_recv->bean_index].process->bean_size);

        /* now we use the new bean pointer and length to instead the
           bean we have register it
        */
        bean_array[INDEX_BEAN_0].process->bean = (char *)pbean_send;
        bean_array[INDEX_BEAN_0].process->bean_size = len;
        BEAN_UPDATE_NOTIFY(bean_sync);
        bean_array[INDEX_BEAN_0].process->bean = (char *)ptemp;
        bean_array[INDEX_BEAN_0].process->bean_size = len_save;
    }
    else if(pbean_recv->bean_sync_action == SYNC_BEAN_RES)
    {
        return -1;
    }
    else if(pbean_recv->bean_sync_action == SYNC_BEAN_FIN)
    {
        /* when the pos of module sync as true, we use the bean from
           other module to update the bean of SCM
        */
        module_sync[pbean_recv->module_id] = true;
    }

    if(pbean_send != NULL)
    {
        free(pbean_send);
    }
    return 0;
}