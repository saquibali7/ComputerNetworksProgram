#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


void display_type(char buffer[])
{
    int alpha_flag = 0;
    int dig_flag = 0;
    int special_flag = 0;
    int i = 0;
    int mylen = 0;
    while (buffer[mylen] != '\0')
    {
        mylen++;
    }
    while (i < mylen)
    {
        if (('a' <= buffer[i] && buffer[i] <= 'z') || ('A' <= buffer[i] && buffer[i] <= 'Z'))
        {
            alpha_flag = 1;
        }
        else if ('0' <= buffer[i] && buffer[i] <= '9')
        {
            dig_flag = 1;
        }
        else if (33 <= buffer[i] && buffer[i] <= 126)
        {
            special_flag = 1;
        }
        i++;
        if (alpha_flag == 1 && dig_flag == 1 && special_flag == 1)
        {
            break;
        }
    }
    if (alpha_flag == 1)
    {
        printf("Alphabet is Exists\n");
    }
    if (dig_flag == 1)
    {
        printf("Numbers is Exist\n");
    }
    if (special_flag == 1)
    {
        printf("Special Character is Exists\n");
    }
}

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[255];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    if (argc < 2)
    {
        fprintf(stderr, "Port No not provided. Program terminated\n");
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("ERROR opening socket");
    }
    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        error("Binding failed. ");
    }

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);

    if (newsockfd < 0)
        error("Error on Accept");

    while (1)
    {
        bzero(buffer, 255);
        n = read(newsockfd, buffer, 255);
        if (n < 0)
            error("Error on reading.");
        printf("Client : %s\n", buffer);
        // call display_type
        display_type(buffer);
        bzero(buffer, 255);
        fgets(buffer, 255, stdin);

        n = write(newsockfd, buffer, strlen(buffer));
        if (n < 0)
        {
            error("Error on Writing.");
        }
        int i = strncmp("Bye", buffer, 3);
        if (i == 0)
            break;
    }
    close(newsockfd);
    close(sockfd);
    return 0;
}