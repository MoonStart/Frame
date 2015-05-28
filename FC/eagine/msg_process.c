#include "common.h"
typedef struct BEAN_ARRAY
{
    BEAN_PROCESS_STRU    *process;
    char                 flag;
} BEAN_ARRAY_STRU;
static BEAN_ARRAY_STRU bean_array[INDEX_BEAN_MAX];
/*****************************************************************************
 Prototype    : process_run
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
void process_run()
{
    BEAN_PROCESS_STRU *head = NULL;
    int index = 0;
    char buffer[MSG_LEN_MAX];
    
    while((index < INDEX_BEAN_MAX))
    {
       if( bean_array[index].flag)
       {
         head = (BEAN_PROCESS_STRU *)bean_array[index].process;
         head->init_bean(head->bean);
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
                 |bean_index | BEAN |
                 |-------------------|
                 */
                /* now we send the new bean to other app*/
                memcpy(buffer, &head->bean_pos, sizeof(int));
                memcpy(buffer+sizeof(int), head->bean, head->bean_size);
                io_send(buffer, head->bean_size+sizeof(int));
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


/*****************************************************************************
 Prototype    : register_msg_container
 Description  : every module message should call this function to register
                own message bean
                to the message array, this module mange all message bean
                all message message bean should be defined as below

                |--------------|--------------|
                |MSG_HEAD_STRU |MSG_BEAN_STRU |
                |--------------|------------- |

                and the every MSG_BEAN_STRU should defined like below

                |-----------|-----------|---------------|
                |parameterx1|parameter-x2|...parameterxx |
                |-----------|-----------|---------------|
 Input        : MSG_HEAD_STRU *head
 Output       : None
 Return Value :
 Calls        :
 Called By    :

  History        :
  1.Date         : 2014/9/11
    Author       : Eason Lee
    Modification : Created function

*****************************************************************************/
int register_to_bean_array(BEAN_PROCESS_STRU *bean_process)
{
    if(bean_process == NULL)
    {
        PRINTF("the message should not be NULL \r\n");
        return -1;
    }


    if(bean_process->bean_pos > INDEX_BEAN_MAX)
    {
        PRINTF("please redefine the message container size or check the message ID \r\n");
        exit(0);
    }

    if(!bean_array[bean_process->bean_pos].flag)
    {
        bean_array[bean_process->bean_pos].process = bean_process;
        bean_array[bean_process->bean_pos].flag = 1;
    }
    else
    {
        PRINTF("the message have register it \r\n");
    }
    return 0;
}

/*****************************************************************************
 Prototype    : msg_process
 Description  : when the io module recive a packect from socket or other stream
                that is just a message bean and the format like below
  |------------------------------------|-----------|-----------|---------------|
  |message bead id(array index)        |parameterx1|parameterx2|...parameterxx |
  |------------------------------------|-----------|-----------|---------------|

  what the different between msg_process and bean_update?
  the msg_process update the msgbean which the value from other module
  and the bean_update update the msgbean which the value from the module himself and
  send the new value to other module
 Input        : void *bean_process
 Output       : None
 Return Value :
 Calls        :
 Called By    :

  History        :
  1.Date         : 2014/9/11
    Author       : Eason Lee
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
           printf("\tNAME:%s \r\n", bean_array[index].process->name);

           if(strcmp(argv[2], "all") == 0)
           {
             printf("\tCONTENT:\r\n");
             bean_array[index].process->display((char*)bean_array[index].process->bean);
           }
         }
        index ++;
       }
    }
    else if(bean_array[atoi(argv[2])].flag)
    {
         printf("\tPOS:%d  \r\n", atoi(argv[2]));
         printf("\tNAME:%s \r\n", bean_array[atoi(argv[2])].process->name);
         printf("\tCONTENT:\r\n");
         bean_array[atoi(argv[2])].process->display((char*)bean_array[atoi(argv[2])].process->bean);
    }
}


#define CMD_BEAN "Bean"

static CMD_TABLE_STRU msgMenu[] =
{   // cmd   sub_cmd_name   cmd_help    sub_cmd_help             fct_call        fct_call2
    { CMD_BEAN, "display",     "-display all bean register array information ",  "display the process array  ",  display,         NULL}
};

/*****************************************************************************
 Prototype    : msg_init
 Description  : we just use this function to register the run function to run list
 Input        : None
 Output       : None
 Return Value :
 Calls        :
 Called By    :

  History        :
  1.Date         : 2014/9/3
    Author       : Eason Lee
    Modification : Created function

*****************************************************************************/
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

UTIL_INIT(SCM, module)
{
   return bean_array_init();
}

UTIL_INIT(CARD1, module)
{
  return bean_array_init();
}





