#ifndef __FUN_MACRO_H__
#define __FUN_MACRO_H__
#include "common.h"



#define BEAN_RUN(name, bean_local)\
    bean_run(name, bean_local)
    
#define BEAN_UPDATE(name, bean_local, bean_receive)\
    bean_update(name, bean_local, bean_receive)
    
#define BEAN_CHECK(name, bean_local)\
    bean_check(name, bean_local)
    
#define BEAN_INIT(name, bean_local)\
    bean_init(name, bean_local)
    
#define BEAN_DISPLAY(name, bean_local)\
    bean_display(name, bean_local)
   
#define BEAN_NOTIFY(beanselfnm, beanbaseonnm, beanself, beanbaseon)\
    bean_notify(beanselfnm, beanbaseonnm, beanself, beanbaseon)
    
#define BEAN_1L_DEF(name, type)\
    bean_1l_def(name, type)

#define BEAN_2L_DEF(name, type)\
    bean_2l_def(name, type)
       
#define BEAN_POINTER(name, p)\
    bean_pointer(name, p)

#define BEAN_BASE_ON(beanself, beanbaseon)\
    bean_base_on(beanself,beanbaseon)

#define BEAN_REGISTER(name)\
    bean_register(name)


#define BEAN_SYNC(name)\
    bean_sync(name)


#endif /* __MSG_PROCESS_H__ */

