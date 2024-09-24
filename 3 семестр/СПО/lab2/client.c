#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>

// void wait_repeat(unsigned int secs) {
//     unsigned int retTime = time(0) + secs;
//     while (time(0) < retTime);
// }

int main(int argc, char *argv[])
{
    int sockfd, connfd, i;
    struct sockaddr_in servaddr, cli;

    if (argc != 4)
    {
        printf("Incorrect number of arguments!\n");
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(1);
    }
    else
    {
        printf("Socket successfully created..\n");
    }

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    servaddr.sin_port = htons((uint16_t) atoi(argv[2]));

    i = atoi(argv[3]);

    printf("i = %d\n", i);

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))!= 0)
    {
        printf("connection with the server failed...\n");
        exit(1);
    }
    else
    {
        printf("connected to the server..\n");
    }

    for (int repeat = 0; repeat < i; repeat++)
    {
        write(sockfd, &i, sizeof(i));
        sleep(1);
        // wait_repeat((unsigned int) i);
    }

    close(sockfd);
}
