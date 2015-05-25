#include "common.h"

#define BUFSIZE 128
//#define IGNORE_CHAR(c) (c == 0x0d)
#define END 0x0a

#define PROMT "HELP"

static char buf_data[BUFSIZE];

int command_line_input_byte(unsigned char c)
{
    static unsigned char overflow = 0; /* Buffer overflow: ignore until END */

    if(IGNORE_CHAR(c))
    {
        return 0;
    }

    if(!overflow)
    {
      buf_data[overflow] = c;
      overflow ++;
      overflow %= BUFSIZE;
    }
    else
    {
        /* Buffer overflowed:
         * Only (try to) add terminator characters, otherwise skip */
        if(c == END)
        {
            /* process */
            printf("%s \r\n", buf_data);
            printf("%s ", PROMT);
            overflow = 0;
        }
    }

    return 1;
}

