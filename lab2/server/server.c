#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../lib/errproc.h"

struct File
{
    char name[64];
    long int size;
    long int data_creation;
    unsigned int number_of_links;
};

int main()
{

    int serverSoc = Socket(AF_INET, SOCK_STREAM, 0);

    //задание адреса
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;    //IPv4
    adr.sin_port = htons(48999); //прослушка на порте
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    Bind(serverSoc, (struct sockaddr *)&adr, sizeof adr);
    Listen(serverSoc, 5);
    socklen_t adrlen = sizeof(adr);

    // сокет для общения с клиентом
    int fd = Accept(serverSoc, (struct sockaddr *)&adr, &adrlen);

    //чтение данных от клиента

    struct File DataIn;
    int countElement;
    int nread;
    char bufer[4096];

    recv(STDOUT_FILENO, &DataIn, sizeof(DataIn), 0);



    // int status_sesion = 1;
    // while (status_sesion)
    // {
    //     nread = recv(fd, &DataIn, sizeof(DataIn), 0);

    //     if (nread == -1)
    //     {
    //         perror("read failure");
    //         exit(EXIT_FAILURE);
    //     }
    //     else if (nread == 0)
    //     {
    //         printf("конец файла");
    //         status_sesion = 0;
    //     }

    //     int sizeInData = 0;
    //     recv(STDOUT_FILENO, &sizeInData, sizeof(sizeInData), 0); // количество элиментов

    //     if (sizeInData < 0)
    //     {
    //         printf("ошибка при считывании количества элементов\n");
    //         status_sesion = 0;
    //     }

    //     struct File DataIn[sizeInData];
    //     for (int i = 0; i < sizeInData; i++)
    //     {
    //         recv(STDOUT_FILENO, &DataIn, sizeof(DataIn), 0); // что полученно от клиента
    //     }

    //    send(fd, &DataIn, nread, 0);
    //     // send(fd, bufer, nread, 0); // отправка ответа
    // }

    close(fd);        // закрытие сокета для связи с клиентом
    close(serverSoc); // закрытие прослушивающего сокета

    return 0;
}
