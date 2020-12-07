#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include "c_public/tcp_client.h"

// g++ tcp_client_tool.cpp c_public/tcp_client.cpp -o tcp_client_tool.out

int main(int argc, char** argv){
    char ip[64];
    int port;
    printf("ip: ");
    scanf("%s", ip);
    printf("port: ");
    scanf("%d", &port);
    TcpClient client;
    client.Connect(ip, port);
    client.StartListen();
    while (1)
    {
        char buffer[64];
        scanf("%s", buffer);
        client.Send(buffer, strlen(buffer));
    }
    client.Close();
    return 0;
}