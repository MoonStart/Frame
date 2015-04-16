#ifndef _COMMON_H_
#define _COMMON_H_



#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>¡¡¡¡¡¡
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
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/select.h>
#include "card_bean.h"
#include "message_id.h"
#include "module_def.h"
#include "msg_process.h"
#include "io_process.h"

typedef void (*pfunc)();

#define DEBUG

#ifdef DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#elif
#define PRINTF
#endif


#endif






