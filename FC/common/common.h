#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#ifdef WIN32
#include <WS2tcpip.h>
#include <winsock.h> 
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
#include "message_id.h"
#include "module_def.h"
#include "msg_process.h"
#include "io_process.h"
#include "cmdline.h"

typedef void (*pfunc)();

#ifdef WIN32
typedef unsigned char bool ;
#define true  1
#define false 0


#define  STDIN_FILENO  STD_INPUT_HANDLE
#define  STDOUT_FILENO STD_OUTPUT_HANDLE
#define  STDERR_FILENO STD_ERROR_HANDLE
#endif

#define DEBUG 1

#ifdef DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#elif
#define PRINTF
#endif


#endif
