#include "common.h"
/*the card init pointer will be define it in different module */
extern pfunc module_main;
int main()
{
    module_main();

    /* call all run function in circle */
    while(1)
    {
        bean_process_run();
    }
}
