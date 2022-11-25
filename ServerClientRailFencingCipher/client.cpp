#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdbool.h>


void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[255];
    if (argc < 3)
    {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        fprintf(stderr, "Error, no such host");
    }

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("Connection Failed");

    while (1)
    {
        bzero(buffer, 255);
        fgets(buffer, 255, stdin);
        // encryption
        int key;
        printf("Enter the key\n");
        scanf("%d", &key);
        int size = strlen(buffer);
        char matrix[key][size];

        for (int i = 0; i < key; i++)
        {
            for (int j = 0; j < size; j++)
            {
                matrix[i][j] = '\n';
            }
        }

        bool down = false;
        int rows = 0, columns = 0;

        for (int i = 0; i < size; i++)
        {
            if (rows == 0 || rows == key - 1)
            {
                down = !down;
            }
            matrix[rows][columns++] = buffer[i];

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
                if (matrix[i][j] != '\n')
                {
                    buffer[k++] = matrix[i][j];
                }
            }
        }
        buffer[k] = '\0';
        // end of encryption
        n = write(sockfd, buffer, strlen(buffer));
        if (n < 0)
            error("Error on writing");

        bzero(buffer, 255);
        n = read(sockfd, buffer, 255);
        if (n < 0)
            error("Error on reading");

        printf("Server : %s\n", buffer);

        int i = strncmp("Bye", buffer, 3);
        if (i == 0)
            break;
    }

    close(sockfd);
    return 0;
}