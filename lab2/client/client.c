#include "../lib/errproc.h"
#include<sys/types.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>    
#include <stdlib.h>
#include <stdio.h>


int main()
{

    int file_di = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in  addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(48999);
    Inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
    Connect(file_di, (struct sockaddr *) &addr, sizeof(addr) );
    
    write(file_di, "THREE HUNDRED BUCKS\n", 21);
    char bufer[1024];
    ssize_t  nread;
    nread = read(file_di, bufer, 1024);

    if(nread == -1){
        perror("read failure");
        exit(EXIT_FAILURE);
    }
    else if(nread == 0){
        printf("EOF: ответ от сервера пуст");
    }
    write(STDOUT_FILENO, bufer, nread);

    close(file_di);
    
    return 0;
}