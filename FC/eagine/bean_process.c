#include "common.h"
typedef struct BEAN_ARRAY
{
    BEAN_PROCESS_STRU    *process;
    char                 flag;
} BEAN_ARRAY_STRU;
static BEAN_ARRAY_STRU bean_array[INDEX_BEAN_MAX];
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
    
    while((index < INDEX_BEAN_MAX))
    {
       if(bean_array[index].flag)
       {
         head = (BEAN_PROCESS_STRU *)bean_array[index].process;
         head->init_bean(head->bean);
		 if(head->bean_size+sizeof(head->bean_pos) > MSG_LEN_MAX)
         {
            printf("the bean %s pos %d too much lager \r\n",head->bean_name, head->bean_pos);
            printf("please redefine the length MSG_LEN_MAX bigger than %d \r\n", head->bean_size+sizeof(head->bean_pos));
         }
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

            if(head->action == EN_ACTION_UPDATE_TO_UP)
            {   
                /*
                 |-------------------|
                 |bean_index | BEAN  |
                 |-------------------|
                 */
                /* now we send the new bean to other app*/
                memcpy(buffer, &head->bean_pos, sizeof(head->bean_pos));
                memcpy(buffer+sizeof(int), head->bean, head->bean_size);
                io_send(buffer, head->bean_size+sizeof(head->bean_pos));
                memset(buffer, 0x00, MSG_LEN_MAX);
                head->action = EN_ACTION_NOCHANGE;
            }
        }
#if 0
        if((head->action == EN_ACTION_UPDATE_TO_DOWN))
        {
          head->update_to_local(head->bean);
          head->action = EN_ACTION_NOCHANGE;
        }
#endif        
        if(io_recv(buffer, MSG_LEN_MAX))
        {
            bean_update(buffer);
            memset(buffer, 0x00, MSG_LEN_MAX);
        }
        index ++;
        index = index % INDEX_BEAN_MAX;
    }
}



void bean_get_pointer(BEAN_PROCESS_STRU *process, char *p)
{
    p = process->bean;
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
void bean_update_notify(BEAN_PROCESS_STRU *bean_process)
{
      UPDATE_NOTIFY_LIST_STRU *update_list  =  bean_process->list;
      BEAN_PROCESS_STRU *temp = NULL;
      
      bean_process->action = EN_ACTION_UPDATE_TO_UP;
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
   UPDATE_NOTIFY_LIST_STRU *p = (UPDATE_NOTIFY_LIST_STRU*)malloc(sizeof(UPDATE_NOTIFY_LIST_STRU));
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


    if(bean_process->bean_pos > INDEX_BEAN_MAX)
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
int bean_update(char *bean_process)
{
    int *index             = NULL;

    BEAN_PROCESS_STRU *head  = NULL;

    if(bean_process == NULL)
    {
      return -1;
    }
    index = (int *)(&bean_process[0]);
    
    if(!bean_array[*index].flag)
    {
        PRINTF("we need't process this message, the message id is %d\r\n", *index);
        return 0;
    }

    head = (BEAN_PROCESS_STRU *)bean_array[*index].process;

    if((0 != memcmp(head->bean, bean_process+sizeof(int), head->bean_size)) && !head->check_para(bean_process + sizeof(int)));
    {
        head->update_to_local(head->bean, bean_process+sizeof(int));
    }

    return 0;
}

/*****************************************************************************
 Prototype    : display
 Description  : display all bean register to the message array
 Input        : None
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2015/4/16
    Author       : Laserly
    Modification : Created function

*****************************************************************************/
static void display(int argc, char** argv)
{
    int index = 0;
    if(argc != 3)
    {
       printf("format: Bean display [all | list | (int)] \r\n");
       return;
    }

    if(strcmp(argv[2], "all") == 0 || strcmp(argv[2], "list") == 0)
    {
      while(index < INDEX_BEAN_MAX)
      {
        if(bean_array[index].flag)
        {
           printf("\tPOS:%d  \r\n", index);
           printf("\tNAME:%s \r\n", bean_array[index].process->bean_name);

           if(strcmp(argv[2], "all") == 0)
           {
             printf("\tCONTENT:\r\n");
             bean_array[index].process->display((char*)bean_array[index].process->bean);
           }
         }
        index ++;
       }
    }
    else if((atoi(argv[2]) <INDEX_BEAN_MAX ) && bean_array[atoi(argv[2])].flag)
    {
         printf("\tPOS:%d  \r\n", atoi(argv[2]));
         printf("\tNAME:%s \r\n", bean_array[atoi(argv[2])].process->bean_name);
         printf("\tCONTENT:\r\n");
         bean_array[atoi(argv[2])].process->display((char*)bean_array[atoi(argv[2])].process->bean);
    }
}


#define CMD_BEAN "Bean"

static CMD_TABLE_STRU msgMenu[] =
{   // cmd   sub_cmd_name   cmd_help    sub_cmd_help             fct_call        fct_call2
    { CMD_BEAN, "display",     "-display all bean register array information ",  "display the process array  ",  display,         NULL}
};



int bean_array_init()
{
    int i = 0;
    while (i < INDEX_BEAN_MAX)
    {
        bean_array[i].flag = 0;
        bean_array[i].process = NULL;
        i++;
    }
    PRINTF("MSG ARRAY INIT OVER \r\n");
    RegisterCommand(msgMenu, sizeof(msgMenu)/sizeof(CMD_TABLE_STRU));
    return 0;
}

BEAN_ARRAY_INIT(SCM, module)
{
   return bean_array_init();
}

BEAN_ARRAY_INIT(CARD1, module)
{
  return bean_array_init();
}





