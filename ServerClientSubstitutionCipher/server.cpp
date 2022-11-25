#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

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
        // **** Decryption ****
        int size = strlen(buffer);
        printf("Before Decryption\n");
        for (int i = 0; i < size; i++)
        {
            printf("%c", buffer[i]);
        }
        printf("\n");
        int key;
        printf("Enter the key\n");
        scanf("%d", &key);
        if (key >= 26)
        {
            key = key % 26;
        }
        int i = 0;
        char ch;
        while (buffer[i] != '\0')
        {
            ch = buffer[i];
            if (ch >= 'a' && ch <= 'z')
            {
                ch = ch - key;
                if (ch < 'a')
                {
                    ch = ch + 'z' - 'a' + 1;
                }
                buffer[i] = ch;
            }
            else if (ch >= 'A' && ch <= 'Z')
            {
                ch = ch - key;
                if (ch > 'Z')
                {
                    ch = ch + 'Z' - 'A' + 1;
                }
                buffer[i] = ch;
            }
            i++;
        }
        // **********
        printf("Client : %s\n", buffer);
        bzero(buffer, 255);
        fgets(buffer, 255, stdin);

        n = write(newsockfd, buffer, strlen(buffer));
        if (n < 0)
        {
            error("Error on Writing.");
        }
        int k = strncmp("Bye", buffer, 3);
        if (k == 0)
            break;
    }
    close(newsockfd);
    close(sockfd);
    return 0;
}