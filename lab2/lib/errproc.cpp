#include "errproc.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

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
}-

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

void Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    int result = connect(sockfd, addr, addrlen);
    if (result == -1)
    {
        perror("connect failure");
        exit(EXIT_FAILURE);
    }
}

void Inet_pton(int af, const char *src, void *dst)
{
    int result = inet_pton(af, src, dst);
    if (result == 0)
    {
        printf("inet_pton failure: src не содержит символов");
    }
    else if (result == -1)
    {
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }
}
