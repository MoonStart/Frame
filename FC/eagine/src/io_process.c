#include "common.h"

#define PORT_SCM  1024
#define PORT_CARD 1025

#define IP_SCM   "127.0.0.1"
#define IP_CARD  "127.0.0.1"

typedef struct SOCK_INFO
{
    unsigned int       sock_fd;
    unsigned short     local_port; /* the port used in local module */
    struct sockaddr_in targetAddr; /* tha target address we will send message to it */
    fd_set             rfd;
    struct timeval     timeout;
    int                maxfd;
    MODULE_NAME_ENUM   module;
    char               send_buffer[MSG_LEN_MAX];
    char               recv_buffer[MSG_LEN_MAX];
} SOCK_INFO_STRU;
static SOCK_INFO_STRU sock_bean;


extern command_line_input_byte(unsigned char c);

static void display()
{
    int i = 0;
    
    printf("sock fd: %d \r\n", sock_bean.sock_fd);

    printf("sock port: %d \r\n", sock_bean.local_port);

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
int io_init(MODULE_NAME_ENUM name)
{
    struct sockaddr_in addr;

    /* for command line tool */
    setvbuf(stdout, (char *)NULL, _IONBF, 0);

    memset(&sock_bean, 0x00, sizeof(SOCK_INFO_STRU));
    memset(&addr, 0x00, sizeof(struct sockaddr_in));

    sock_bean.module = name;
    sock_bean.targetAddr.sin_family = AF_INET;

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
    PRINTF("sock fd is %d \r\n", sock_bean.sock_fd);
    PRINTF("port is %d \r\n", sock_bean.local_port);

    sock_bean.timeout.tv_sec = 0;
    sock_bean.timeout.tv_usec = 1000;


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
    return 0;
}

IO_INIT(SCM, module)
{
  io_init(module);
}

IO_INIT(CARD1, module)
{
  io_init(module);
}

int io_recv(char *buffer, unsigned short len)
{
    int nRet = 0;
    int rlen = 0;
    unsigned char c;
    

    FD_ZERO(&sock_bean.rfd);

    FD_SET(sock_bean.sock_fd, &sock_bean.rfd);
    FD_SET(STDIN_FILENO, &sock_bean.rfd);

    sock_bean.maxfd = (sock_bean.sock_fd > STDIN_FILENO ? sock_bean.sock_fd:STDIN_FILENO)  + 1;
    
    nRet = select(sock_bean.maxfd, &sock_bean.rfd, NULL, NULL, &sock_bean.timeout);
    if (nRet < 0)
    {
        perror("select:");
        return -1;
    }
    else
    {   
        /* read the message from socket */
        if (FD_ISSET(sock_bean.sock_fd, &sock_bean.rfd))
        {
            rlen = recvfrom(sock_bean.sock_fd, sock_bean.recv_buffer, MSG_LEN_MAX, 0, NULL, NULL);
            if (rlen < 0)
            {
              perror("recvfrom:");
            }
            else
            {
              memcpy(buffer, sock_bean.recv_buffer, rlen);
            }
        }
        /* read a chcarator from stdin */
        if(FD_ISSET(STDIN_FILENO, &sock_bean.rfd))
        {
          if(read(STDIN_FILENO, &c, 1) > 0)
          {
            command_line_input_byte(c);
          }
        }
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
    memcpy(sock_bean.send_buffer, buffer, len);

    ret = sendto(sock_bean.sock_fd, sock_bean.send_buffer, len, 0, (struct sockaddr *)&sock_bean.targetAddr, sizeof(sock_bean.targetAddr));
    if(len != ret)
    {
      perror("sendto:");
    }
    PRINTF("%d byte have send \r\n", len);
    return ret;
}

