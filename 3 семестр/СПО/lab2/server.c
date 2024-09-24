#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void read_childproc(int sig)
{
   int status;

   pid_t id = waitpid (-1, &status, WNOHANG); // Вызов функции waitpid () для уничтожения дочернего процесса

   if(WIFEXITED(status))
   {
      printf("Removed proc id: %d \n",id);
      printf("Child send: %d \n",WEXITSTATUS(status));
   }
}

void func(int connfd)
{
    int i = 0;

    read(connfd, &i, sizeof(i));
    printf("Recv: %d\n", i);

    for (int repeat = 0; repeat < (i - 1); repeat++)
    {
        read(connfd, &i, sizeof(i));
        printf("Recv: %d\n", i);
    }
}

int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
    pid_t child;

    signal(SIGCHLD, read_childproc);

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
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = 0;

    if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) {
        printf("Socket bind failed...\n");
        exit(1);
    }
    else
    {
        printf("Socket successfully binded..\n");
    }

    len = sizeof(servaddr);
    if (getsockname(sockfd, (struct sockaddr *) &servaddr, &len))
    {
        printf("Failed getsockname...\n");
        exit(1);
    }

    printf("Port number: %d\n", htons(servaddr.sin_port));

    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(1);
    }
    else
    {
        printf("Server listening..\n");
    }

    len = sizeof(cli);

    while (1)
    {
        connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
        if (connfd < 0) {
            printf("server accept failed...\n");
            exit(1);
        }
        else
            printf("server accept the client...\n");

        child = fork();

        if (child < 0)
        {
            printf("Failed create child process...\n");
            exit(1);
        }
        else if (child == 0)
        {
            close(sockfd);
            func(connfd);
            close(connfd);
            exit(0);
        }
    }

    close(sockfd);
}
