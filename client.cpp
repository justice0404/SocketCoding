#include <iostream>
#include <string>
#include <cstring>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

using std::string;

int main(int argc, char const *argv[])
{
    /* code */
    int sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sockfd < 0)
    {
        printf("Create socket errno: errnno=%d errmsg=%s\n",errno,strerror(errno));
        return 1;
    }
    else{
        printf("Create socket success!|n");
    }

    string ip = "127.0.0.1";
    int port = 8085;

    struct sockaddr_in sockaddr;
    std::memset(&sockaddr,0,sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    sockaddr.sin_port = htons(port);
    if(connect(sockfd,(struct sockaddr *)&sockaddr,sizeof(sockaddr)) < 0)
    {
        printf("socket connet error: errno=%d errmsg=%s\n",errno,strerror(errno));
        return 1;
    }

    string data = "hello world";
    send(sockfd,data.c_str(),data.size(),0);

    char buf[1024] = {0};
    recv(sockfd,buf,sizeof(buf),0);

    printf("recv: %s\n",buf);

    close(sockfd);

    return 0;
}
