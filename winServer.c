// Socket @Souvikarjun Deb
// Socket Server.c - Windows Version

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

void error(char *msg) {
    fprintf(stderr, "%s: %d\n", msg, WSAGetLastError());
    exit(1);
}

int main(int argc, char *argv[]) {
    
    if(argc < 2) {
        fprintf(stderr, "port number not provided\n");
        exit(1);
    }

    WSADATA wsaData;
    SOCKET sockfd, newsockfd;
    int portno, n;
    char buffer[256];

    struct sockaddr_in server_addr, client_addr;
    int clilen;

    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        error("WSAStartup failed");
    }

    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sockfd == INVALID_SOCKET) {
        error("ERROR opening socket");
    }

    ZeroMemory((char *) &server_addr, sizeof(server_addr));
    portno = atoi(argv[1]);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(portno);
    
    if(bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) <0 ){
        error("Binding Faild");
    }

    listen(sockfd, 3);

    clilen = sizeof(client_addr);

    newsockfd = accept(sockfd, (struct sockaddr *) &client_addr , &clilen);

    if(newsockfd<0){
        error("Error while on accept");
    }
    fprintf(stdout, "Connected to the client\n");
    while (1)
    {
        ZeroMemory(buffer, 256);
        n = recv(newsockfd, buffer, 255, 0);
        if (n == SOCKET_ERROR ){
            error("Reading Failed");
        }
        printf("Client : %s", buffer);
        ZeroMemory(buffer, 256);
        fgets(buffer, 255, stdin);

        n = send(newsockfd, buffer, 255, 0);
        if(n == SOCKET_ERROR){
            error("Writing Failed");
        }

        int i = strncmp("GoodBye", buffer, 7);
        if (i==0)
        {
            break;
        }
    
    }

    closesocket(newsockfd);
    closesocket(sockfd);
    WSACleanup();
    return 0;   
}