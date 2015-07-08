#include "common.h"

BEAN_ARRAY_STRU bean_array[BEAN_ARRAY_SIZE]; /* the base bean */

NOTIFY_LIST_STRU bean_list[LIST_ARRAY_SIZE]; /* may be is not enough */

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

    while(1)
    {
        head = (BEAN_PROCESS_STRU *)bean_array[index].process;

        if(bean_array[index].flag)
        {
            head->run(head->bean);
        }

        memset(buffer, 0x00, MSG_LEN_MAX);
        if(io_instance.bean_recv(buffer, MSG_LEN_MAX))
        {
            bean_update_to_local(buffer);
        }
        index ++;
        index = index % BEAN_ARRAY_SIZE;
    }
}


void bean_base_on(BEAN_PROCESS_STRU *pup, BEAN_PROCESS_STRU *pbaseon, notify func, char *name)
{
   static int index = 0;

   if(index > LIST_ARRAY_SIZE)
   {
     printf("please define the macro LIST_ARRAY_SIZE much more lager \r\n");
     exit(0);
   }

   if(pup==NULL || pbaseon==NULL || func==NULL || name==NULL)
   {
      printf("%s %d parameter error \r\n", __func__, __LINE__);
      exit(0);
   }
   
   NOTIFY_LIST_STRU *plist = &bean_list[index];

   plist->notify_func_name = name;
   plist->bean_process = pup;
   plist->notify_to = func;

   /* add to the base bean notify list */
   plist->next = pbaseon->notify_list;
   pbaseon->notify_list = plist;
   index ++;
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
    BEAN_PROCESS_STRU *temp  = NULL; /* just only notify child */
    NOTIFY_LIST_STRU *list = bean_process->notify_list;

    while(list != NULL)
    {
        temp = (BEAN_PROCESS_STRU *)list->bean_process;

        if(bug_instance.bean_callstack)
        {
           bean_process->display(bean_process->bean);
           temp->display(temp->bean);
           printf("\t %s(%s %s)\r\n",list->notify_func_name,bean_process->bean_name, temp->bean_name);
           bean_process->display(bean_process->bean);
           temp->display(temp->bean);
           printf("\r\n\r\n\r\n");
        }

        list->notify_to(bean_process->bean, temp->bean);
        list = list->next;
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
    static unsigned index = 0;
    int i = 0;
    if(bean_process == NULL)
    {
        printf("the bean should not be NULL \r\n");
        return -1;
    }

    if(index>BEAN_ARRAY_SIZE)
    {
        printf("please redefine the message container size or check the message ID \r\n");
        printf("bean name %s \r\n", bean_process->bean_name);
        exit(0);
    }

    printf("\r\n\r\n###### %s init satrt ######\r\n",bean_process->bean_name);
    bean_process->init_bean(bean_process->bean);
    bean_process->display(bean_process->bean);
    printf("###### %s init over ######\r\n",bean_process->bean_name);

    if((bean_process->bean_type == BEAN_LEVEL_0) && !bean_array[index].flag)
    {
        bean_array[index].process = bean_process;
        bean_array[index].flag = 1;

        /* we sum the name[i] as the bean id, because every bean name is 
           different, so the id is different
        */
        while(bean_process->bean_name[i] != '\0')
        {
           bean_process->bean_id += bean_process->bean_name[i];
           i++;
        }

        bean_process->bean_id += (card_instance.shelf+card_instance.slot+card_instance.card)
        /* the buffer need to be lager than beansize + beanindex + moduleid */
        if((bean_process->bean_size + 4 + 4) > MSG_LEN_MAX)
        {
           printf("the bean %s pos %d too much lager \r\n", bean_process->bean_name, bean_process->bean_pos);
           printf("please redefine the length MSG_LEN_MAX bigger than %d \r\n", bean_process->bean_size + 8);
        }
       // module_info.bean_count++;
    }

    index++;
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
    BEAN_PROCESS_STRU *head  = NULL;
    MSG_HEAD_STRU *head_msg = (MSG_HEAD_STRU *)bean_msg;
    if(head_msg == NULL)
    {
        return -1;
    }

    if(head_msg->pos == 0xFFFFFFFF)
    {
        for()
    }


    if(module_info.ModuleId == MODULE_SCM &&
            (head_msg->pos != 0) &&
            !module_sync_info[head_msg->moduleid])
    {
        printf("the module %d haven't finished sync action \r\n", head_msg->moduleid);
        return 0;
    }

    
    if(
        (head_msg->index>BEAN_ARRAY_SIZE) || 
        (!bean_array[head_msg->index].flag) || 
        (bean_array[head_msg->index].process->bean_type == BEAN_LEVEL_1))
    {
        PRINTF("we need't process this message, the message id is %d\r\n", head_msg->index);
        return 0;
    }

    head = (BEAN_PROCESS_STRU *)bean_array[head_msg->index].process;

    if((0 != memcmp(head->bean, head_msg->bean, head->bean_size)) && !head->check_para(head_msg->bean));
    {
        head->update(head->bean, head_msg->bean);
    }

    return 0;
}


int bean_array_init(MODULE_NAME_ENUM module)
{
    int i = 0;


    while (i < BEAN_ARRAY_SIZE)
    {
        bean_array[i].flag = 0;
        bean_array[i].process = NULL;
        i++;
    }
    
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





