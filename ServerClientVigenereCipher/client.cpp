#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define KEY_SIZE 20

// vignere cipher


char table[26][26];

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int p=0;
    for(int i=0;i<26;i++){
        for(int j=0;j<26;j++){
            table[i][j]=(p+j)%26+97;
        }
        p++;
    }
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
        buffer[strlen(buffer) - 1] = '\0';
        int i = 0;
        while (buffer[i] != '\0')
        {
            if (buffer[i] >= 'A' && buffer[i] <= 'Z')
            {
                buffer[i] = buffer[i] - 'A' + 'a';
            }
            i++;
        }
        char key[KEY_SIZE];
        printf("Enter your key :\n");
        fgets(key, KEY_SIZE, stdin);
        key[strlen(key) - 1] = '\0';
        int keySize = strlen(key);
        i = 0;
        while (key[i] != '\0')
        {
            if (key[i] >= 'A' && key[i] <= 'Z')
            {
                key[i] = key[i] - 'A' + 'a';
            }
            i++;
        }
        i = 0;
        int j = 0;
        int row, column;
        while (buffer[i] != '\0')
        {
            row = buffer[i] - 'a';
            column = key[j] - 'a';
            buffer[i] = table[row][column];
            i++;
            j++;
            j = j % keySize;
        }
        n = write(sockfd, buffer, strlen(buffer));
        if (n < 0)
            error("Error on writing");

        bzero(buffer, 255);
        n = read(sockfd, buffer, 255);
        if (n < 0)
            error("Error on reading");

        printf("Server : %s\n", buffer);

        int k = strncmp("Bye", buffer, 3);
        if (k == 0)
            break;
    }

    close(sockfd);
    return 0;
}