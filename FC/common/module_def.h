#ifndef MODULE_DEF_H_
#define MODULE_DEF_H_

typedef enum MODULE_NAME
{ 
  MODULE_SCM = 0,
  MODULE_CARD,
  MODULE_MAX               
}MODULE_NAME_ENUM;

typedef int (*callback_init)(MODULE_NAME_ENUM);

typedef struct CALL_INIT
{
  // callback_init cspii_init; /* any parameter get from user */
   callback_init io_init; /* socket or serial init */
  // callback_init hal_init; /* interface for hardware*/
  // callback_init driver_init; /* hardware init */
   callback_init bean_array_init;
  //callback_init util_init; /*any tools init */
}CALL_INIT_STRU;


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
                                           /*cspii_##name##_init,*/\
                                           io_##name##_init,\
                                           /*hal_##name##_init,*/\
                                           /*driver_##name##_init,*/\
                                           bean_array_##name##_init\
                                           /*util_##name##_init\*/\
                                           };\
         int index = 0;\
         int size = sizeof(CALL_INIT_STRU)/sizeof(callback_init);\
         callback_init *pfinit = (callback_init *)&name##_callback;\
         do\
         {\
             while(index < size)\
             {\
                (*pfinit)(module);\
                pfinit ++;\
                index ++;\
             }\
         }while(0);
#endif /* MODULE_DEF */


