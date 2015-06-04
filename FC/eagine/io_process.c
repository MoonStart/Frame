#include "common.h"

BEAN_IO_STRU io_instance;



#ifdef WIN32	
#pragma comment(lib, "Ws2_32.lib")
#endif

#define PORT_SCM  1024
#define PORT_CARD 1025

#define IP_SCM   "127.0.0.1"
#define IP_CARD  "127.0.0.1"

typedef struct SOCK_INFO
{
#ifdef WIN32
	SOCKET sock_fd;
#else
    unsigned int       sock_fd;
#endif
    unsigned short     local_port; /* the port used in local module */
    struct sockaddr_in targetAddr; /* tha target address we will send message to it */
    fd_set             rfd;
    struct timeval     timeout;
    int                maxfd;
    MODULE_NAME_ENUM   module;
#if WIN32
    char               send_buffer[MSG_LEN_MAX];
    char               recv_buffer[MSG_LEN_MAX];
#endif
} SOCK_INFO_STRU;
static SOCK_INFO_STRU sock_bean;


static void display(int argc, char** argv)
{
    int i = 0;
    
    printf("sock fd: %d \r\n", sock_bean.sock_fd);

    printf("sock port: %d \r\n", sock_bean.local_port);
#if WIN32
    printf("\r\nRECV BUFFER:\r\n");
    for(i = 0; i < 16; i++)
    {
        printf("|%2d ", i);
    }
    printf("|\r\n");
    for(i = 0; i < MSG_LEN_MAX; i++)
    {
        printf("|%2x ", sock_bean.recv_buffer[i]);
        if((i+1)%16 == 0)printf("|\r\n");
    }

    printf("\r\nSEND BUFFER:\r\n");
    for(i = 0; i < 16; i++)
    {
        printf("|%2d ", i);
    }
    printf("|\r\n");
    for(i = 0; i < MSG_LEN_MAX; i++)
    {
        printf("|%2x ", sock_bean.send_buffer[i]);
        if((i+1)%16 == 0)printf("|\r\n");
    }
#endif
}

static CMD_TABLE_STRU ioMenu[] =
{   // cmd   sub_cmd_name   cmd_help    sub_cmd_help             fct_call        fct_call2
    { "io", "display",     "display all io information ",  "display the socket  ",  display,         NULL}
};

/*****************************************************************************
 Prototype    : io_init
 Description  : create socket and register the run function to the function
                list, the function just be called only once
                we bind different port for different module
 Input        : None
 Output       : None
 Return Value :
 Calls        :
 Called By    :

  History        :
  1.Date         : 2014/4/2
    Author       : Eason Lee
    Modification : Created function

*****************************************************************************/
int io_init(MODULE_NAME_ENUM name)
{
#ifdef WIN32
    WSADATA wsaData;
    int iErrorMsg;  
	int rlt;
#endif
    struct sockaddr_in addr;

    /* for command line tool */
    setvbuf(stdout, (char *)NULL, _IONBF, 0);

    memset(&sock_bean, 0x00, sizeof(SOCK_INFO_STRU));
    memset(&addr, 0x00, sizeof(struct sockaddr_in));

    sock_bean.module = name;
    sock_bean.targetAddr.sin_family = AF_INET;

#ifdef WIN32
    iErrorMsg = WSAStartup(MAKEWORD(1,1),&wsaData);   
    if (iErrorMsg != NO_ERROR)  
    {    
        printf("wsastartup failed with error : %d\n",iErrorMsg);  
        rlt = 1;  
        return rlt;  
    } 
#endif

    
    switch(name)
    {
    case MODULE_SCM:
        sock_bean.local_port = PORT_SCM;
        sock_bean.targetAddr.sin_port = htons(PORT_CARD);
        inet_pton(AF_INET, IP_CARD, &sock_bean.targetAddr.sin_addr);
        break;
    case MODULE_CARD:
        sock_bean.local_port = PORT_CARD;
        sock_bean.targetAddr.sin_port = htons(PORT_SCM);
        inet_pton(AF_INET, IP_SCM, &sock_bean.targetAddr.sin_addr);
        break;
    default:
        PRINTF("error MODULE NAME \r\n");
        return -1;
    }

    sock_bean.sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_bean.sock_fd == -1)
    {
        printf("socket()\n");
        return -1;
    }

    /* prepared for select function */
    sock_bean.timeout.tv_sec = 0;
    sock_bean.timeout.tv_usec = 0;
#ifdef WIN32
    sock_bean.maxfd = 0;
#else
    sock_bean.maxfd = (sock_bean.sock_fd > STDIN_FILENO ? sock_bean.sock_fd:STDIN_FILENO)  + 1;
#endif

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(sock_bean.local_port);
    inet_pton(AF_INET,"127.0.0.1", &addr.sin_addr);

    if (bind(sock_bean.sock_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        perror("bind:");
        return -1;
    }

    PRINTF("IO INIT OVER \r\n");

    RegisterCommand(ioMenu, sizeof(ioMenu) / sizeof(CMD_TABLE_STRU));
#ifdef WIN32
     CreateThread(NULL, 1024, (LPTHREAD_START_ROUTINE)win32_cmd_process, 0, 0, NULL);
#endif
    return 0;
}

IO_INIT(SCM, module)
{
  io_instance.bean_recv = io_recv;
  io_instance.bean_send = io_send;
  return io_init(module);
}

IO_INIT(CARD1, module)
{
  io_instance.bean_recv = io_recv;
  io_instance.bean_send = io_send;
  return io_init(module);
}

int io_recv(char *buffer, unsigned short len)
{
    int nRet = 0;
    int rlen = 0;
    char *line = NULL;
    unsigned char c;

    FD_ZERO(&sock_bean.rfd);
    FD_SET(sock_bean.sock_fd, &sock_bean.rfd);

#ifdef WIN32
#else
    FD_SET(STDIN_FILENO, &sock_bean.rfd);
#endif

    nRet = select(sock_bean.maxfd, &sock_bean.rfd, NULL, NULL, &sock_bean.timeout);
    if (nRet < 0)
    {
        perror("select:");
        exit(0);
    }
    else
    {   
        /* read the message from socket */
        if (FD_ISSET(sock_bean.sock_fd, &sock_bean.rfd))
        {
            rlen = recvfrom(sock_bean.sock_fd, buffer, MSG_LEN_MAX, 0, NULL, NULL);
            if (rlen < 0)
            {
              perror("recvfrom:");
              rlen = 0;
            }
#if WIN32
              memcpy(sock_bean.recv_buffer, buffer, rlen);
#endif
        }

#ifdef WIN32
#else
        /* read a chcarator from stdin */
        if(FD_ISSET(STDIN_FILENO, &sock_bean.rfd))
        {
          if(read(STDIN_FILENO, &c, 1) > 0)
          {
            command_line_input_byte(c);
          }
        }
#endif
    }
    return rlen;
}

int io_send(char *buffer, unsigned short len)
{
    int ret = 0;

    /* call it by another module */
    if(len > MSG_LEN_MAX)
    {
        return -1;
    }
#if WIN32
    memcpy(sock_bean.send_buffer, buffer, len);
#endif

    ret = sendto(sock_bean.sock_fd, buffer, len, 0, (struct sockaddr *)&sock_bean.targetAddr, sizeof(sock_bean.targetAddr));
    if(len != ret)
    {
      perror("sendto:");
    }
    return ret;
}

