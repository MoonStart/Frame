#include "common.h"

BEAN_ARRAY_STRU bean_array[INDEX_BEAN_ALL];


MODULE_INFO_STRU module_info;
unsigned char module_sync_info[MODULE_MAX] = {false};


/*****************************************************************************
 Prototype    : bean_process_run
 Description  : this function continuly run in main function
 Input        : None
 Output       : None
 Return Value :
 Calls        :
 Called By    :

  History        :
  1.Date         : 2014/9/10
    Author       : Eason Lee
    Modification : Created function

*****************************************************************************/
void bean_process_run()
{
    BEAN_PROCESS_STRU *head = NULL;
    int index = 0;
    char buffer[MSG_LEN_MAX];
    MSG_HEAD_STRU *head_msg = (MSG_HEAD_STRU *)buffer;

    while(index < INDEX_BEAN_ALL)
    {
        if(bean_array[index].flag)
        {
            head = (BEAN_PROCESS_STRU *)bean_array[index].process;
            head->init_bean(head->bean);
            if(head->bean_size + sizeof(head->bean_pos) > MSG_LEN_MAX)
            {
                printf("the bean %s pos %d too much lager \r\n", head->bean_name, head->bean_pos);
                printf("please redefine the length MSG_LEN_MAX bigger than %d \r\n", head->bean_size + sizeof(head->bean_pos));
            }
            module_info.bean_count++;
        }
        index ++;
    }

    index = 0;
    while(1)
    {
        head = (BEAN_PROCESS_STRU *)bean_array[index].process;

        if(bean_array[index].flag)
        {
            head->update_from_local(head->bean);
        }

        memset(buffer, 0x00, MSG_LEN_MAX);
        if(io_instance.bean_recv(buffer, MSG_LEN_MAX))
        {
            bean_update_to_local(buffer);
        }
        index ++;
        index = index % INDEX_BEAN_ALL;
    }
}



void bean_get_pointer(BEAN_PROCESS_STRU *process, char **p)
{
    *p = process->bean;
}


int bean_update_to_out(BEAN_PROCESS_STRU *bean_process)
{
    char buffer[MSG_LEN_MAX];
    MSG_HEAD_STRU *head_msg = (MSG_HEAD_STRU *)buffer;
    /*
     |-------------------------------|
     |moduleid | bean_index | BEAN  |
     |-------------------------------|
     */
    /* now we send the new bean to other app*/
    memset(buffer, 0x00, MSG_LEN_MAX);
    head_msg->moduleid = module_info.ModuleId;
    head_msg->index = bean_process->bean_pos;
    memcpy(head_msg->bean, bean_process->bean, bean_process->bean_size);
    return io_instance.bean_send(buffer, MSG_LEN_MAX);
}
/*****************************************************************************
 Prototype    : bean_update_notify
 Description  : one bean updated and some bean updated base the bean which
                regisetr the base bead list
 Input        : BEAN_PROCESS_STRU *bean_process
 Output       : None
 Return Value :
 Calls        :
 Called By    :

  History        :
  1.Date         : 2015/6/1
    Author       : Laserlee
    Modification : Created function

*****************************************************************************/
void bean_update_notify_list(BEAN_PROCESS_STRU *bean_process)
{
    UPDATE_NOTIFY_LIST_STRU *update_list  =  bean_process->list;
    BEAN_PROCESS_STRU *temp = NULL;

    while(update_list != NULL)
    {
#ifdef DEBUG
        temp = container_of(update_list, BEAN_PROCESS_STRU, list);
        printf("update the %s \r\n", temp->bean_name);
#endif
        update_list->pNotify(bean_process->bean);
        update_list = update_list->next;
    }
}

/*****************************************************************************
 Prototype    : bean_add_list
 Description  : add the notify list to the bean notify list
 Input        : BEAN_PROCESS_STRU *bean_process
                notify func
 Output       : None
 Return Value :
 Calls        :
 Called By    :

  History        :
  1.Date         : 2015/6/1
    Author       : Laserlee
    Modification : Created function

*****************************************************************************/
void bean_add_list(BEAN_PROCESS_STRU *bean_process, notify func)
{
    UPDATE_NOTIFY_LIST_STRU *p = (UPDATE_NOTIFY_LIST_STRU *)malloc(sizeof(UPDATE_NOTIFY_LIST_STRU));
    if(p != NULL)
    {
        p->pNotify = func;
        p->next  = bean_process->list;
        bean_process->list = p;
    }
}

/*****************************************************************************
 Prototype    : bean_register_to_array
 Description  : register the bean to the bean process array
 Input        : BEAN_PROCESS_STRU *bean_process
 Output       : None
 Return Value :
 Calls        :
 Called By    :

  History        :
  1.Date         : 2015/6/1
    Author       : Laserlee
    Modification : Created function

*****************************************************************************/
int bean_register_to_array(BEAN_PROCESS_STRU *bean_process)
{
    if(bean_process == NULL)
    {
        printf("the message should not be NULL \r\n");
        return -1;
    }


    if(bean_process->bean_pos > INDEX_BEAN_ALL)
    {
        printf("please redefine the message container size or check the message ID \r\n");
        printf("bean name %s \r\n", bean_process->bean_name);
        exit(0);
    }

    if(!bean_array[bean_process->bean_pos].flag)
    {
        bean_array[bean_process->bean_pos].process = bean_process;
        bean_array[bean_process->bean_pos].flag = 1;
    }
    else
    {
        PRINTF("the bean have register it \r\n");
    }
    return 0;
}

/*****************************************************************************
 Prototype    : bean_update
 Description  : if we received a new which have been registered we should
                update the local bean and set it to the hardware.
 Input        : char *bean_process
 Output       : None
 Return Value :
 Calls        :
 Called By    :

  History        :
  1.Date         : 2015/6/1
    Author       : Laserlee
    Modification : Created function

*****************************************************************************/
int bean_update_to_local(char *bean_msg)
{
    int *index             = NULL;

    BEAN_PROCESS_STRU *head  = NULL;
    MSG_HEAD_STRU *head_msg = (MSG_HEAD_STRU *)bean_msg;
    if(head_msg == NULL)
    {
        return -1;
    }

    if(module_info.ModuleId == MODULE_SCM &&
            (head_msg->index != INDEX_BEAN_0) &&
            !module_sync_info[head_msg->moduleid])
    {
        printf("the module %d haven't finished sync action \r\n", head_msg->moduleid);
        return 0;
    }

    if(!bean_array[head_msg->index].flag)
    {
        PRINTF("we need't process this message, the message id is %d\r\n", *index);
        return 0;
    }

    head = (BEAN_PROCESS_STRU *)bean_array[head_msg->index].process;

    if((0 != memcmp(head->bean, head_msg->bean, head->bean_size)) && !head->check_para(head_msg->bean));
    {
        head->update_to_local(head->bean, head_msg->bean);
    }

    return 0;
}



extern void bean_test_menu_register();
int bean_array_init(MODULE_NAME_ENUM module)
{
    int i = 0;


    while (i < INDEX_BEAN_ALL)
    {
        bean_array[i].flag = 0;
        bean_array[i].process = NULL;
        i++;
    }

    module_info.ModuleId = module;
    module_info.bean_count = 0;
    PRINTF("MSG ARRAY INIT OVER \r\n");
    bean_test_menu_register();
    return 0;
}

BEAN_ARRAY_INIT(SCM, module)
{
    return bean_array_init(module);
}

BEAN_ARRAY_INIT(CARD1, module)
{
    return bean_array_init(module);
}





