#include "common.h"
static int bean_sync_count = 0;


BEAN_UPDATE_UP(bean_sync, bean_local)
{
  char buffer[MSG_LEN_MAX] = "";
  MSG_HEAD_STRU *head_msg = (MSG_HEAD_STRU *)buffer;
  MODULE_BEAN_STRU *pbean_local = (MODULE_BEAN_STRU *)bean_local;
  unsigned int index = 0; /* becareful */


  pbean_local->module_id = module_info.ModuleId;
  /* if have been do sync, just return do nothing
     first bean need't been sync 
  */
  if(module_info.bean_count == (bean_sync_count+1))
    return 0;

  while(1)
  {
     if(bean_array[index].flag && (index != 0))
     {
        pbean_local->bean_index = index;
        pbean_local->bean_sync_action = SYNC_BEAN_REQ;

        head_msg->module_id = module_info.ModuleId;
        head_msg->index = INDEX_BEAN_0; /* sync bean call */
        memcpy(head_msg->bean, bean_array[0].process->bean, bean_array[0].process->bean_size);

        io_instance.bean_send(buffer, MSG_LEN_MAX);
        memset(buffer, 0x00, MSG_LEN_MAX);
     }

     if(io_instance.bean_recv(buffer, MSG_LEN_MAX))
     {
        bean_update(buffer);
        memset(buffer, 0x00, MSG_LEN_MAX);
     }
  
     if(module_info.bean_count == (bean_sync_count+1))
     {
        memset(buffer, 0x00, MSG_LEN_MAX);
        pbean_local->bean_sync_action = SYNC_BEAN_FIN;
        pbean_local->module_id = module_info.ModuleId;
        
        head_msg->module_id = module_info.ModuleId;
        head_msg->index = INDEX_BEAN_0; /* sync bean call */
        memcpy(head_msg->bean, bean_array[0].process->bean, bean_array[0].process->bean_size);
        io_instance.bean_send(buffer, MSG_LEN_MAX);
        break;
     }
     index ++;
     index = index % INDEX_BEAN_MAX;
  }
   return 0;
}



BEAN_UPDATE_DOWN(bean_sync, bean_local, bean_receive)
{
  MODULE_BEAN_STRU *pbean_local = (MODULE_BEAN_STRU *)bean_local;
  MODULE_BEAN_STRU *pbean_recv =  (MODULE_BEAN_STRU *)bean_receive;
  MODULE_BEAN_STRU *pbean_send = NULL; /* the bean will be send */

  BEAN_PROCESS_STRU *process_temp = NULL; /* for bean_sync */

  if(module_info.bean_count == (bean_sync_count+1))
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
     memcpy(bean_array[pbean_recv->bean_index].process->bean,
            pbean_recv->bean, 
            bean_array[pbean_recv->bean_index].process->bean_size);
     bean_sync_count++;
     return 0;
  }
  else if(pbean_recv->bean_sync_action == SYNC_BEAN_FIN)
  { 
     return -1;
  }
 
  return 0;
}