#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../lib/errproc.h"

int main()
{

    int serverSoc = Socket(AF_INET, SOCK_STREAM, 0);

    //задание адреса
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;    //IPv4
    adr.sin_port = htons(48999); //прослушка на порте
    Bind(serverSoc, (struct sockaddr *)&adr, sizeof adr);
    Listen(serverSoc, 5);
    socklen_t adrlen = sizeof(adr);
    // сокет для общения с клиентом
    int fd = Accept(serverSoc, (struct sockaddr *)&adr, &adrlen);

    //чтение данных от клиента
    ssize_t nread;
    char bufer[1024];

    int status_sesion = 1;
    while (status_sesion)
    {

        nread = read(fd, bufer, 1024);

        if (nread == -1)
        {
            perror("read failure");
            exit(EXIT_FAILURE);
        }
        else if (nread == 0)
        {
            printf("конец файла");
            status_sesion = 0;
        }
        write(STDOUT_FILENO, bufer, nread); // что полученно от клиента

        write(fd, bufer, nread); // отправка ответа
    }

    close(fd);        // закрытие сокета для связи с клиентом
    close(serverSoc); // закрытие прослушивающего сокета

    return 0;
}
