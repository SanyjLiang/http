#include "http.h"
#include <myhead.h>

#define SIZE 4096

int init_server(int port)
{
    //创建套接字
    int sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock==-1)
    {
        perror("socket error");
        return -1;
    }

    //端口号快速重用
    int reuse=1;
    if(setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse))==-1)
    {
        perror("setsockopt error");
        return -1;
    }

    //绑定IP地址和端口号
    struct sockaddr_in local;
    local.sin_family=AF_INET;
    local.sin_port=htons(port);
    local.sin_addr.s_addr=INADDR_ANY;  //表示可以接收任意主机的连接请求

    if(bind(sock,(struct sockaddr*)&local,sizeof(local))==-1)
    {
        perror("bind error");
        return -1;
    }

    //启动监听
    if(listen(sock,128)==-1)
    {
        perror("listen error");
        return -1;
    }

    //程序执行至此，说明服务器创建成功
    return sock;
}

//用于处理客户端信息函数的定义
int handler_msg(int sock)
{
    //定义容器存储客户端发来的数据
    char del_buf[SIZE]="";
    
    //读取客户端发来的请求
    //通常我们使用recv来接收客户端请求时，最后一个参数是0表示阻塞读取，并将数据读走
    //而最后一个参数为MSG_PEEK时，仅仅只是表示查查看套接字中的数据，并不读走
    recv(sock,del_buf,SIZE,MSG_PEEK); 

    #if 1
    printf("------------------------------------------\n");
    printf("%s\n",del_buf);
    printf("------------------------------------------\n");
    #endif

    return 0;
}