#include "common.h"

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
static void display(int argc, char **argv)
{
    int index = 0;
    if(argc != 3 && argc != 2)
    {
        printf("format: Bean list ([index(int)]optinal) \r\n");
        return;
    }

    if(argc == 2)
    {
        while(index < INDEX_BEAN_ALL)
        {
            if(bean_array[index].flag)
            {
                printf("\r\n\tPOS:%d  \r\n", index);
                printf("\tNAME:%s \r\n", bean_array[index].process->bean_name);
            }
            index ++;
        }
    }
    else if((atoi(argv[2]) < INDEX_BEAN_ALL ) && bean_array[atoi(argv[2])].flag)
    {
        printf("\r\n\tPOS:%d  \r\n", atoi(argv[2]));
        printf("\tNAME:%s \r\n", bean_array[atoi(argv[2])].process->bean_name);
        printf("\tCONTENT:\r\n");
        bean_array[atoi(argv[2])].process->display((char *)bean_array[atoi(argv[2])].process->bean);
    }
}

static void setcardbean(int argc, char **argv)
{
    char *p = NULL;
    CARD_MSG_BEAN_STRU *plocal = NULL;

    BEAN_POINTER(EDFA, p);
    plocal = (CARD_MSG_BEAN_STRU *)p;
    if(argc != 4)
    {
        printf("command format: Bean Name [x|y|z] value(int) \r\n");
        return;
    }

    if(strcmp(argv[2], "x") == 0)
    {
        plocal->x = atoi(argv[3]);
        BEAN_UP_NOTIFY(EDFA);
    }
}



#define CMD "Bean"
CMD_TABLE_STRU beanMenu[] =
{
    // cmd        sub_cmd_name               cmd_help                                 sub_cmd_help                                      fct_call        fct_call2
    {CMD,        "list",          "-display or set bean content register in array",            "-show detail ",      display,         NULL},
    {NULL,       STRING(EDFA),    "-Set the Bean content",                          "-the bean name ",               setcardbean,     NULL},
};


void bean_test_menu_register()
{
   RegisterCommand(beanMenu, sizeof(beanMenu) / sizeof(CMD_TABLE_STRU));
}