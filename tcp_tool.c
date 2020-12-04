#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

#define MAXLINE 4096

int main(int argc, char** argv){
    char ip[64];
    int port;
    printf("ip: ");
    scanf("%s", ip);
    printf("port: ");
    scanf("%d", &port);
    fflush(stdin);



    int   sockfd, n;
    char  recvline[4096], sendline[4096];
    struct sockaddr_in  servaddr;

    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
        return 0;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    if( inet_pton(AF_INET, ip, &servaddr.sin_addr) <= 0){
        printf("inet_pton error\n");
        return 0;
    }

    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
        printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
        return 0;
    }

    while (1)
    {
        printf("send msg to server: \n");
        fgets(sendline, 4096, stdin);
        printf(" start send msg to server: \n");
        if( send(sockfd, sendline, strlen(sendline), 0) < 0){
            printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
            return 0;
        }
        n = recv(sockfd, recvline, MAXLINE, 0);
        recvline[n] = '\0';
        printf("%s\n", recvline);
    }
    close(sockfd);
    return 0;
}