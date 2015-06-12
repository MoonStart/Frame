#ifndef _MODULE_BEAN_H_
#define _MODULE_BEAN_H_
typedef enum BEAN_SYNC_ACTION
{   
    SYNC_BEAN_RESET = 0,
    SYNC_BEAN_REQ,      /* request */
    SYNC_BEAN_RES,     /* response */
    SYNC_BEAN_FIN      /* finish */
} BEAN_SYNC_ACTION_ENUM;

#define STR_BEAN_SYNC_ACTION(action) \
    (action == SYNC_BEAN_RESET)? "SYNC_BEAN_RESET":\
    (action == SYNC_BEAN_REQ) ? "SYNC_BEAN_REQ":\
    (action == SYNC_BEAN_RES) ? "SYNC_BEAN_RES":\
    (action == SYNC_BEAN_FIN) ? "SYNC_BEAN_FIN":"UNKNOWN"

typedef struct MODULE_BEAN
{   
    unsigned int           des_moduleid;
    unsigned int           src_moduleid;
    BEAN_SYNC_ACTION_ENUM  bean_sync_action;
    unsigned int           bean_sync_index; /*the bean which will to updated exclude this bean */
    char bean[0];
} MODULE_BEAN_STRU;

#endif
