#ifndef MODULE_DEF_H_
#define MODULE_DEF_H_

typedef enum MODULE_NAME
{
    MODULE_SCM = 0,
    MODULE_CARD,
    MODULE_MAX
} MODULE_NAME_ENUM;
#define STR_MODULE_NAME(module)\
    (module == MODULE_SCM)?"MODULE_SCM":\
    (module == MODULE_CARD)?"MODULE_CARD":"UNKNOWN"

typedef struct MODULE_INFO
{
    MODULE_NAME_ENUM ModuleId;
    int bean_count;
} MODULE_INFO_STRU;



typedef int (*callback)(MODULE_NAME_ENUM);

typedef struct CALLBACK
{
    callback func;
    char *   func_name;
}CALLBACK_STRU;

typedef struct CALL_INIT
{
    // CALLBACK_STRU cspii_init; /* any parameter get from user */
    CALLBACK_STRU io_init; /* socket or serial init */
    // CALLBACK_STRU hal_init; /* interface for hardware*/
    // CALLBACK_STRU driver_init; /* hardware init */
    CALLBACK_STRU bean_array_init;
    //CALLBACK_STRU util_init; /*any tools init */
} CALL_INIT_STRU;


#define CSPII_INIT(name, module)\
    int cspii_##name##_init(MODULE_NAME_ENUM module)

#define IO_INIT(name, module)\
    int io_##name##_init(MODULE_NAME_ENUM module)

#define HAL_INIT(name, module)\
    int hal_##name##_init(MODULE_NAME_ENUM module)

#define DRIVER_INIT(name, module)\
    int driver_##name##_init(MODULE_NAME_ENUM module)

#define BEAN_ARRAY_INIT(name, module)\
    int bean_array_##name##_init(MODULE_NAME_ENUM module)

#define UTIL_INIT(name, module)\
    int util_##name##_init(MODULE_NAME_ENUM module)


#define INIT_HEAD(name, module)\
  /*extern CSPII_INIT(name, module);*/\
    extern IO_INIT(name, module);\
    /*extern HAL_INIT(name, module);*/\
    /*extern DRIVER_INIT(name, module);*/\
    /*extern UTIL_INIT(name, module);*/\
    extern BEAN_ARRAY_INIT(name, module);

#define INIT_LIST(name, module)\
    INIT_HEAD(name, module)\
    static CALL_INIT_STRU name##_callback = {\
                                           /* {cspii_##name##_init,        STRING(cspii_##name##_init)},*/\
                                              {io_##name##_init,           STRING(io_##name##_init)},\
                                           /* {hal_##name##_init,          STRING(hal_##name##_init)},*/\
                                           /* {driver_##name##_init,       STRING(driver_##name##_init)}, */\
                                              {bean_array_##name##_init,   STRING(bean_array_##name##_init)},\
                                           /* {util_##name##_init,         STRING(util_##name##_init)} */\
                                           };\
         int index = 0;\
         int size = sizeof(CALL_INIT_STRU)/sizeof(CALLBACK_STRU);\
         CALLBACK_STRU *pfinit = (CALLBACK_STRU *)&name##_callback;\
         do\
         {\
             while(index < size)\
             {\
                printf("\r\n\r\n******* %s call start ******* \r\n", pfinit->func_name);\
                pfinit->func(module);\
                printf("******* %s call over ******\r\n", pfinit->func_name);\
                pfinit ++;\
                index ++;\
             }\
         }while(0);
#endif /* MODULE_DEF */


