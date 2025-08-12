// Socket @Souvikarjun Deb
// Socket client.c


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

void error(char *msg){
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]){
    
    int sockfd, portno, n;
    struct sockaddr_in server_addr;
    struct hostent *server;

    char buffer[256];
    if (argc<3){
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        exit(1);
    }

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("Error Opening Socket");
    }

    server = gethostbyname(argv[1]);
    if (server == NULL) 
    {
        fprintf(stderr, "Server doesn't exist");
    }

    bzero((char * ) &server_addr, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr_list[0], (char *) &server_addr.sin_addr.s_addr, server->h_length);
    server_addr.sin_port = htons(portno);
    if(connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr))<0 ){
        error("Connection Faild");
    }

    while (1)
    {
        bzero(buffer, 255);
        fgets(buffer, 255, stdin);
        n = write(sockfd, buffer, strlen(buffer));
        if(n<0){
            error("Writing Failed");
        }
        bzero(buffer, 255);
        n = read(sockfd, buffer, 255);
        if (n<0)
        {
            error("Reading Failed");
        }
        printf("Server: %s", buffer);

        int i = strncmp("GoodBye", buffer, 7);
        if (i==0)
        {
            break;
        }
        
    }

    close(sockfd);
    return 0;
    
    
        
}