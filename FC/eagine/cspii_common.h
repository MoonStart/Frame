#ifndef __CSPII_COMMON_H_
#define __CSPII_COMMON_H_

typedef enum MODULE_NAME
{
    MODULE_SCM = 0,
    MODULE_CARD,
    MODULE_MAX
} MODULE_NAME_ENUM;

#define STR_MODULE_NAME(module)\
    (module == MODULE_SCM)?"MODULE_SCM":\
    (module == MODULE_CARD)?"MODULE_CARD":"UNKNOWN"

typedef struct CARD_INFO
{
    uint32 shelf;
    uint32 slot;
    uint32 card;
} CARD_INFO_STRU;

#endif


