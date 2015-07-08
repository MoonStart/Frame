#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#ifdef WIN32
#include <WS2tcpip.h>
#include <winsock2.h>
#else
#include <unistd.h>
#include <sys/types.h>¡¡¡¡
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/file.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/ftp.h>
#include <arpa/inet.h>
#include <arpa/telnet.h>
#include <signal.h>
#include <errno.h>
#include <netdb.h>
#include <sys/select.h>
#endif
#include "card_bean.h"
#include "bean_index.h"
#include "module_def.h"
#include "bean_process.h"
#include "io_process.h"
#include "cmdline.h"
#include "module_bean.h"
#include "bean_test_menu.h"
#include "cspii_common.h"
#include "card_alarm.h"
#include "fun_macro.h"

typedef void (*pfunc)();

#ifdef WIN32
typedef unsigned char bool ;
#define true  1
#define false 0
#endif


#define container_of(ptr, type, member)\
        (type *)((char *)ptr - offsetof(type,member))

#define DEBUG 1
#define STRING(x) #x


#ifdef DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF
#endif


typedef unsigned int   uint32;
typedef unsigned char  uint8;
typedef unsigned short uint16;


#endif
