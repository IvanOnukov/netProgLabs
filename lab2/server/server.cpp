#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errprog.h>
int Socket(int domain, int types, int protocol)
{
    int result = socket(domain, types, protocol);

    if (result == -1)
    {
        //ошибка неверный файловый дискриптор
        perror("soket failed");
        exit(EXIT_FAILURE);
    }
    return result;
}

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    int result = bind(sockfd, addr, addrlen);
    if (result == -1)
    {
        // обишибка связывания сокета с адресом
        perror("bind  failed");
        exit(EXIT_FAILURE);
    }
}

void Listen(int sockfd, int backlog)
{
    int result = listen(sockfd, backlog);
    if (result == -1)
    {
        // ошибка прослущивания порта
        perror("listen  failed");
        exit(EXIT_FAILURE);
    }
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
    int result = accept(sockfd, addr, addrlen);
    if (result == -1)
    {
        // ошибка подключения
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
    return result;
}

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
    int file_di = Accept(serverSoc, (struct sockaddr *)&adr, &adrlen);

    //чтение данных от клиента
    ssize_t nread;
    char bufer[1024];

    nread = read(file_di, bufer, 1024);

    if (nread == -1)
    {
        perror("read failure");
        exit(EXIT_FAILURE);
    }
    else if (nread == 0)
    {
        printf("конец файла");
    }
    write(STDOUT_FILENO, bufer, nread); // что полученно от клиента
    write(file_di, bufer, nread);       // отправка ответа

    // close(file_di); // закрытие сокета для связи с клиентом 
    // close(listen); // закрытие прослушивающего сокета 
    
    return 0;
}
