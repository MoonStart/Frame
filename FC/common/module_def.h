#ifndef MODULE_DEF_H_
#define MODULE_DEF_H_

typedef enum MODULE_NAME
{ 
  MODULE_SCM = 0,
  MODULE_CARD,
  MODULE_MAX               
}MODULE_NAME_ENUM;

typedef int(*callback_init)(MODULE_NAME_ENUM Module);

typedef struct CALL_INIT
{
   callback_init cspii_init; /* any parameter get from user */
   callback_init io_init; /* socket or serial init */
   callback_init hal_init; /* interface for hardware*/
   callback_init driver_init /* hardware init */;
   callback_init util_init; /*any tools init */
}CALL_INIT_STRU;


#define CSPII_INIT(name, module) \
    int cspii_##name##_init(MODULE_NAME_ENUM Module)


#define IO_INIT(name, module) \
    int io_##name##_init(MODULE_NAME_ENUM Module)


#define HAL_INIT(name, module) \
    int hal_##name##_init(MODULE_NAME_ENUM Module)

#define DRIVER_INIT(name, module) \
    int driver_##name##_init(MODULE_NAME_ENUM Module)

#define UTIL_INIT(name, module) \
    int util_##name##_init(MODULE_NAME_ENUM Module)


#define INIT_LIST(name, module) \
    extern CSPII_INIT(name); \
    extern IO_INIT(name); \
    extern HAL_INIT(name); \
    extern DRIVER_INIT(name); \
    extern UTIL_INIT(name); \
    static CALL_INIT name##_callback = { \
                                           CSPII_INIT(name), \
                                           IO_INIT(name), \
                                           HAL_INIT(name), \
                                           DRIVER_INIT(name),\
                                           UTIL_INIT(name) \
                                           };\
         do \
         {  \
             int index = 0;\
             int size = sizeof(name##_callback)/sizeof(callback_init); \
             callback_init *pfinit = (callback_init*)&name##_callback; \
             while(index < size) \
             { \
                (*pfinit)(module); \
                pfinit ++;
             } \
         }while(0) 
#endif /* MODULE_DEF */


