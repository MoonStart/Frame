#include "common.h"
typedef struct MSG_ARRAY
{
    MSG_PROCESS_STRU    *pmsg;
    char                 flag;
} MSG_ARRAY_STRU;
static MSG_ARRAY_STRU msg_array[INDEX_BEAN_MAX];
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
    MSG_PROCESS_STRU *head = NULL;
    int index = 0;
    char buffer[MSG_LEN_MAX];

    while((index < INDEX_BEAN_MAX) && msg_array[index].flag)
    {
        head = (MSG_PROCESS_STRU *)msg_array[index].pmsg;
        head->init(head->buffer);
        index ++;
    }


    index = 0;
    while(1)
    {
        head = (MSG_PROCESS_STRU *)msg_array[index].pmsg;

        if(msg_array[index].flag)
        {
            if(!head->sync(head->buffer) && (head->action == EN_ACTION_SYNC))
            {
                memcpy(buffer, &head->index, sizeof(int));
                /*
                 |-------------------|
                 |MSG_ID | BEAN |
                 |-------------------|
                 */
                memcpy(buffer+sizeof(int), head->buffer, head->len);
                io_send(buffer, head->len + sizeof(int));
            }
        }
        sleep(1);
        if(io_recv(buffer, MSG_LEN_MAX))
        {
            msg_update(buffer);
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
int register_to_msg_array(MSG_PROCESS_STRU *msg)
{
    if(msg == NULL)
    {
        PRINTF("the message should not be NULL \r\n");
        return -1;
    }


    if(msg->index > INDEX_BEAN_MAX)
    {
        PRINTF("please redefine the message container size or check the message ID \r\n");
        exit(0);
    }

    if(!msg_array[msg->index].flag)
    {
        msg_array[msg->index].pmsg = msg;
        msg_array[msg->index].flag = 1;
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

  what the different between msg_process and msg_update?
  the msg_process update the msgbean which the value from other module
  and the msg_update update the msgbean which the value from the module himself and
  send the new value to other module
 Input        : void *msg
 Output       : None
 Return Value :
 Calls        :
 Called By    :

  History        :
  1.Date         : 2014/9/11
    Author       : Eason Lee
    Modification : Created function

*****************************************************************************/
int msg_update(byte *msg)
{
    int *index             = NULL;

    MSG_PROCESS_STRU *head  = NULL;

    if(msg == NULL)
    {
      return -1;
    }
    index = (int *)(&msg[0]);

    
    if(!msg_array[*index].flag)
    {
        PRINTF("we need't process this message, the message id is %d\r\n", *index);
        return 0;
    }

    head = (MSG_PROCESS_STRU *)msg_array[*index].pmsg;

    if(!head->check(msg + sizeof(int)) && (0 == memcmp(head->buffer, msg+sizeof(int), head->len)));
    {
        head->set(head->buffer, msg+sizeof(int));
    }

    return 0;
}

/*****************************************************************************
 Prototype    : msg_list
 Description  : list all message bean in the message container
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
void msg_list()
{
    int index = 0;
    MSG_PROCESS_STRU *head = NULL;

    while(index < INDEX_BEAN_MAX)
    {
        head =  (MSG_PROCESS_STRU *)msg_array[index].pmsg;
        PRINTF("\t %s \r\n", head->name);
    }
}


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
int msg_array_init()
{
    int i = 0;
    while (i < INDEX_BEAN_MAX)
    {
        msg_array[i].flag = 0;
        msg_array[i].pmsg = NULL;
        i++;
    }
    PRINTF("MSG ARRAY INIT OVER \r\n");
    return 0;
}

UTIL_INIT(SCM, module)
{
   return msg_array_init();
}

UTIL_INIT(SCM, module)
{
  return msg_array_init();
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
void display()
{
    int index = 0;
    printf("the bean register to the array: \r\n");

    while(index < INDEX_BEAN_MAX)
    {
       if(msg_array[index].flag)
       {
        printf("%s \r\n" msg_array[index].pmsg.name);
       }
    }
    return 0;
}
