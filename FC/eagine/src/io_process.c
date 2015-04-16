#include "common.h"

#define PORT_SCM  1024
#define PORT_CARD 1025

typedef struct SOCK_INFO
{
    unsigned int   sock_fd;
    unsigned short serv_port;
    struct sockaddr_in targetAddr;
    MODULE_NAME_ENUM module;
    char           send_buffer[MSG_LEN_MAX];
    char           recv_buffer[MSG_LEN_MAX];
} SOCK_INFO_STRU;
static SOCK_INFO_STRU sock_bean;


int display()
{
    int i = 0;

    PRINTF("sock fd: %d \r\n", sock_bean.sock_fd);

    PRINTF("sock port: %d \r\n", sock_bean.serv_port);

    PRINTF("RECV BUFFER\r\n");
    for(i = 0; i < 16; i++)
    {
        PRINTF("|%2d ", i);
    }
    PRINTF("\r\n");
    for(i = 0; i < MSG_LEN_MAX; i++)
    {
        if(i % 16 == 0)
        {
            PRINTF("\r\n");
        }

        PRINTF("|%2x ", sock_bean.recv_buffer[i]);
    }

    PRINTF("SEND BUFFER\r\n");
    for(i = 0; i < 16; i++)
    {
        PRINTF("|%2d ", i);
    }
    PRINTF("\r\n");
    for(i = 0; i < MSG_LEN_MAX; i++)
    {
        if(i % 16 == 0)
        {
            PRINTF("\r\n");
        }

        PRINTF("|%2x ", sock_bean.send_buffer[i]);
    }
}


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
char io_init(MODULE_NAME_ENUM name)
{
    struct sockaddr_in addr;

    memset(&sock_bean, 0x00, sizeof(SOCK_INFO_STRU));
    memset(&addr, 0x00, sizeof(struct sockaddr_in));

    switch(name)
    {
    case MODULE_SCM:
        sock_bean.serv_port = PORT_SCM;
        sock_bean.targetAddr.sin_port = htons(PORT_CARD);
        break;
    case MODULE_CARD:
        sock_bean.serv_port = PORT_CARD;
        sock_bean.targetAddr.sin_port = htons(PORT_SCM);
        break;
    default:
        PRINTF("error MODULE NAME \r\n");
        return -1;
    }

    
    sock_bean.module = name;
    sock_bean.targetAddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &sock_bean.targetAddr.sin_addr);


    sock_bean.sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_bean.sock_fd == -1)
    {
        printf("socket()\n");
        return -1;
    }
    PRINTF("sock fd is %d \r\n", sock_bean.sock_fd);
    PRINTF("port is %d \r\n", sock_bean.serv_port);
    
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(sock_bean.serv_port);
    inet_pton(AF_INET,"127.0.0.1", &addr.sin_addr);

    if (bind(sock_bean.sock_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        printf("bind()/n");
        return -1;
    }

    PRINTF("IO INIT OVER \r\n");
    return 0;
}


int io_recv(char *buffer, unsigned short len)
{
    int nRet = 0;
    fd_set rfd;
    struct timeval timeout;
    int maxfd = 0;
    
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;

    FD_ZERO(&rfd);

    FD_SET(sock_bean.sock_fd, &rfd);

    maxfd = sock_bean.sock_fd + 1;
    
    nRet = select(maxfd, &rfd, NULL, NULL, &timeout);
    if (nRet == -1)
    {
        printf("select()/n");
        return -1;
    }
    else
    {
        if (FD_ISSET(sock_bean.sock_fd, &rfd))
        {
            int nRet = recvfrom(sock_bean.sock_fd, sock_bean.recv_buffer, MSG_LEN_MAX, 0, NULL, NULL);
            if (nRet == -1)
            {
                printf("recvfrom()/n");
            }
            perror("error:");
            PRINTF("%d byte recived \r\n");
        }
    }
    memcpy(buffer, sock_bean.recv_buffer, nRet);
    return nRet;
}

int io_send(char *buffer, unsigned short len)
{
    int ret = 0;

    /* call it by another module */
    if(len > MSG_LEN_MAX)
    {
        return -1;
    }
    memcpy(sock_bean.send_buffer, buffer, len);

    ret = sendto(sock_bean.sock_fd, sock_bean.send_buffer, MSG_LEN_MAX, 0, (struct sockaddr *)&sock_bean.targetAddr, sizeof(sock_bean.targetAddr));
    perror("error:");
    PRINTF("%d byte have send \r\n");
    return ret;
}

