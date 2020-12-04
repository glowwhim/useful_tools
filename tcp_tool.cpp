#include <stdio.h>
#include "c_public/tcp_client.h"

// g++ tcp_tool.cpp c_public/tcp_client.cpp -o tcp_tool

int main(int argc, char** argv){
    char ip[64];
    int port;
    printf("ip: ");
    scanf("%s", ip);
    printf("port: ");
    scanf("%d", &port);
    fflush(stdin);
    TcpClient client;
    client.Run(ip, port);
    return 0;
}