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

    int num1, num2, answer, choice;

S:  n= write(newsockfd, "Enter Number 1: ", strlen("Enter Number 1"));
    if (n<0)
    {
        error("Error Writing to socket");
    }
    read(newsockfd,&num1, sizeof(int));
    printf("Client - number 1 is : %d\n", num1);
    
    n= write(newsockfd, "Enter Number 2: ", strlen("Enter Number 2"));
    if (n<0)
    {
        error("Error Writing to socket");
    }
    read(newsockfd,&num2, sizeof(int));
    printf("Client - number 2 is : %d\n", num2);
    
    n= write(newsockfd, "Enter choice: \n1.Addition \n2.Substraction \n3.Multiplication \n4.Division \n5.Exit ", strlen("Enter choice: \n1.Addition \n2.Substraction \n1.Multiplication \n1.Division \n5.Exit"));
    if (n<0)
    {
        error("Error Writing to socket");
    }
    read(newsockfd,&choice, sizeof(int));
    printf("Client - choiceis : %d\n", choice);

    switch (choice)
    {
    case 1:
        answer = num1 + num2;
        break;
    case 2:
        answer = num1 - num2;
        break;
    case 3:
        answer = num1 * num2;
        break;
    case 4:
        answer = num1 / num2;
        break;
    case 5:
        goto Q;
        break;
    }

    write(newsockfd, &answer, sizeof(int));
    if(choice!=5) {
        goto S;
    }
    
Q:  close(newsockfd);
    close(sockfd);
    return 0;
    
}
