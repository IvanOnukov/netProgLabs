#include "../lib/errproc.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

struct File
{
    char name[64];
    long int size;
    long int data_creation;
    unsigned int number_of_links;
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
    struct File DataOut={"lol", 1234, 908, 1};

    send(fd, &DataOut, sizeof(DataOut), 0);

    // while (arg == 1)
    // {
    //     printf("Введите количество вайлов\n");
    //     unsigned int size_arr = 0;
    //     scanf("%u", &size_arr);

    //     struct File DataOut[size_arr];

    //     send(fd, &size_arr, sizeof(size_arr), 0);

    //     for (int i = 0; i < size_arr; i++)
    //     {
    //         printf("номер файла  %d  общее количество  %d\n", i + 1, size_arr);

    //         printf("Введите имя файла\n");
    //         scanf("%s", DataOut[i].name);

    //         printf("Введите размер файла\n");
    //         scanf("%ld", &DataOut[i].size);

    //         printf("Введите дату создания в Unix стандарте  файла\n");
    //         scanf("%ld", &DataOut[i].data_creation);

    //         printf("Введите количество сылак на файлы\n");
    //         scanf("%u", &DataOut[i].number_of_links);
    //     }

    //     for (int i = 0; i < size_arr; i++)
    //     {
    //         send(fd, &DataOut[i], sizeof(DataOut[i]), 0);
    //     }

    //     long int sizeSearch;
    //     printf("Введите интересующий размер файла\n");
    //     scanf("%ld", &sizeSearch);

    //     send(fd, &sizeSearch, sizeof(sizeSearch), 0);

    //     char bufer[4096];
    //     ssize_t nread;
    //     nread = read(fd, bufer, 4096);

    //     if (nread == -1)
    //     {
    //         perror("read failure");
    //         exit(EXIT_FAILURE);
    //     }
    //     else if (nread == 0)
    //         printf("EOF: ответ от сервера пуст");

    //     recv(STDOUT_FILENO, bufer, nread, 0); //вывод от сервера

    //     printf("\n1) continue\n2) stop\n");
    //     scanf("%d", &arg);
    // }
    close(fd);

    return 0;
}