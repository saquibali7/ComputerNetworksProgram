#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define KEY_SIZE 20

// vignere cipher 


char table[26][26];

void error(const char *msg)
{
    perror(msg);
    exit(1);
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
        // ********** Decryption ***********
        char key[KEY_SIZE];
        printf("Enter your key :\n");
        fgets(key, KEY_SIZE, stdin);
        key[strlen(key) - 1] = '\0';
        int keySize = strlen(key);
        int i = 0;
        while (key[i] != '\0')
        {
            if (key[i] >= 'A' && key[i] <= 'Z')
            {
                key[i] = key[i] - 'A' + 'a';
            }
            i++;
        }
        printf("Before Decryption Client : %s\n", buffer);
        i = 0;
        int j = 0, k = 0;
        int row = 0, column = 0;
        while (buffer[i] != '\0')
        {
            column = key[j] - 'a';
            for (k = 0; k < 26; k++)
            {
                if (table[k][column] == buffer[i])
                {
                    break;
                }
            }
            buffer[i] = k + 'a';
            i++;
            j++;
            j = j % keySize;
        }
        // printf("After Decryption :\n");
        // // *************************
        printf("After decryption Client : %s\n", buffer);
        bzero(buffer, 255);
        fgets(buffer, 255, stdin);

        n = write(newsockfd, buffer, strlen(buffer));
        if (n < 0)
        {
            error("Error on Writing.");
        }
        int l = strncmp("Bye", buffer, 3);
        if (l == 0)
            break;
    }
    close(newsockfd);
    close(sockfd);
    return 0;
}