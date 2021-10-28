#include "../lib/errproc.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

struct Book
{
    char avtor[64];
    char name[64];
    char publicer[64];
    int year;
    int num_page;
};

int main()
{

    int fd = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(48999);
    Inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
    Connect(fd, (struct sockaddr *)&addr, sizeof(addr));
    
    int arg;
    printf("1) start\n2) stop\n");
    scanf("%d", &arg);

    while (arg == 1)
    {
        char avtor_name[32];
        printf("Введите имя автора\n");
        scanf("%s", avtor_name);

        write(fd, avtor_name, strlen(avtor_name));
        char bufer[1024];
        ssize_t nread;
        nread = read(fd, bufer, 1024);

        if (nread == -1)
        {
            perror("read failure");
            exit(EXIT_FAILURE);
        }
        else if (nread == 0)
        {
            printf("EOF: ответ от сервера пуст");
        }
        
        write(STDOUT_FILENO, bufer, nread);//вывод от сервера 
                
        printf("\n1) continue\n2) stop\n");
        scanf("%d", &arg);
    }
    close(fd);

    return 0;
}