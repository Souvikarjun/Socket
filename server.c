// Socket @Souvikarjun Deb
// Socket Server.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

void error(char *msg){
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]){
    
    if(argc < 2){
        fprintf(stderr, "port number not provided\n");
        exit(1);
    }

    int sockfd, newsockfd, portno, n;
    char buffer[256];

    struct sockaddr_in server_addr, client_addr;
    socklen_t clilen;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("ERROR opening socket");
    }

    bzero((char *) &server_addr, sizeof(server_addr));
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

    while (1)
    {
        bzero(buffer, 255);
        n = read(newsockfd, buffer, 255);
        if (n <0 ){
            error("Reading Failed");
        }
        printf("Client : %s", buffer);
        bzero(buffer, 255);
        fgets(buffer, 255, stdin);

        n = write(newsockfd, buffer, 255);
        if(n<0){
            error("Writing Failed");
        }

        int i = strncmp("GoodBye", buffer, 7);
        if (i==0)
        {
            break;
        }
    
    }

    close(newsockfd);
    close(sockfd);
    return 0;
    
}

