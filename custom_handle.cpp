#include "custom_handle.h"
#include <myhead.h>
#define KB 1024
#define HTML_SIZE (64*1024)

//处理求和的相关逻辑
static int handle_add(int sock,const char*req_buf)
{
    int num1,num2;  //存储传过来的两个数据

    //使用函数，将数据解析出来
    sscanf(req_buf,"\"data1=%ddata2=%d\"",&num1,&num2);

    char reply_buf[HTML_SIZE]="";
    sprintf(reply_buf,"%d",num1+num2);      //将和转换为字符串
    printf("reply_buf=%s\n",reply_buf);

    send(sock,reply_buf,strlen(reply_buf),0);

    return 0;
}


//处理相关数据使用的函数
int parse_and_process(int sock,const char* querry_string,char *req_buf)
{
    //先处理求和请求
    if(strstr(req_buf,"data1=")&&strstr(req_buf,"data2="))
    {
        return handle_add(sock,req_buf);
    }else
    {
        //处理其他请求
    }

    return 0;
}