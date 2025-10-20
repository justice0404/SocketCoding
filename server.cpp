#include <iostream>
#include <cstring>
#include <string>
using std::string;

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    /* code */
    //1.创建socket
    int sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sockfd < 0)
    {
        printf("Create socket error : errno = %d errmsg = %s\n",errno,strerror(errno));
        return 1;
    }
    else{
        printf("Create socket success!\n");
    }


    //2.绑定ip
    string  ip = "127.0.0.1";
    int port = 8085;

    struct sockaddr_in sockaddr;
    std::memset(&sockaddr,0,sizeof(sockaddr));  //清洗sockaddr的内存地址，置为0
    sockaddr.sin_family = AF_INET;  //协议族
    sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());   //绑定ip地址，接收const char*的指针
    sockaddr.sin_port = htons(port);    //转换字节大小端，针对16位数
    if(bind(sockfd,(struct sockaddr *)&sockaddr,sizeof(sockaddr)) < 0)
    {
        printf("socket bind error:errno=%d,errmsg=%s\n",errno,strerror(errno));
        return 1;
    }
    else
    {
        printf("socket bind success:ip=%s port=%d\n",ip.c_str(),port);
    }

    while (true)
    {
        /* code */
        int connfd = accept(sockfd,nullptr,nullptr);
        if(connfd < 0)
        {
            printf("socket accept error:error=%d errmsg=%s\n",errno,strerror(errno));
            return 1;
        }

        char buf[1024] = {0};
        size_t len = recv(connfd,buf,sizeof(buf),0);
        printf("rece:conn=%d msg=%s\n",connfd,buf);

        send(connfd,buf,len,0);
    }
    
    close(sockfd);

    return 0;
}
