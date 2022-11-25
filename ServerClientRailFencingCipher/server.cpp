#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>


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
        // *****
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
        char matrix[key][size];

        for (int i = 0; i < key; i++)
        {
            for (int j = 0; j < size; j++)
            {
                matrix[i][j] = '\n';
            }
        }

        bool down;
        int rows = 0, columns = 0;

        for (int i = 0; i < size; i++)
        {
            if (rows == 0)
            {
                down = true;
            }
            if (rows == key - 1)
            {
                down = false;
            }
            matrix[rows][columns++] = '*';

            if (down == true)
            {
                rows++;
            }
            else
            {
                rows--;
            }
        }
        int k = 0;
        for (int i = 0; i < key; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (matrix[i][j] == '*' && k < size)
                {
                    matrix[i][j] = buffer[k++];
                }
            }
        }
        k = 0;
        rows = 0, columns = 0;
        for (int i = 0; i < size; i++)
        {
            if (rows == 0)
            {
                down = true;
            }
            if (rows == key - 1)
            {
                down = false;
            }
            if (matrix[rows][columns] != '\n')
            {
                buffer[k++] = matrix[rows][columns++];
            }
            if (down == true)
            {
                rows++;
            }
            if (down == false)
            {
                rows--;
            }
        }
        // *****
        printf("Client : %s\n", buffer);
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