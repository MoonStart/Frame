#ifndef _MODULE_BEAN_H_
#define _MODULE_BEAN_H_
typedef enum BEAN_SYNC_ACTION
{
    SYNC_BEAN_REQ = 0, /* request */
    SYNC_BEAN_RES,     /* response */
    SYNC_BEAN_FIN      /* finish */
} BEAN_SYNC_ACTION_ENUM;



typedef struct MODULE_BEAN
{
    MODULE_NAME_ENUM       module_id;
    BEAN_SYNC_ACTION_ENUM  bean_sync_action;
    unsigned int           bean_index;
    char bean[0];
} MODULE_BEAN_STRU;

#endif
