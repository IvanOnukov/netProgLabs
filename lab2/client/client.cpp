#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
// #include <string>
#include <iostream>
#include <cstring>
//#include "../lib/errproc.h"
#include "../lib/struct.cpp"

#define SERVER_IP "127.0.0.1"
#define DEFAULT_PORT 47999 // 47999
#define CLIENT_ER "CLIENT ERROR: "
#define CLIENT "CLIENT: "

void RecvArrayElements(std::string *sourse_array, uint32_t &array_size, int fd)
{
    for (int i = 0; i < array_size; i++)
    {
        uint32_t send_size_el;
        recv(fd, &send_size_el, sizeof(uint32_t), 0);
        send_size_el = ntohl(send_size_el);

        char bufer[send_size_el];

        recv(fd, &bufer, send_size_el, 0);
        sourse_array[i].assign(bufer, sizeof(bufer));
    }
}

void PrintArray(std::string *source_array, const int &array_size)
{
    for (int i = 0; i < array_size; i++)
    {
        std::cout << source_array[i] << "\t";
    }
    std::cout << std::endl;
}
int main()
{

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("socket create fail");
    }

    struct sockaddr_in server_adr;

    server_adr.sin_family = AF_INET;
    server_adr.sin_port = htons(DEFAULT_PORT);

    inet_pton(AF_INET, SERVER_IP, &server_adr.sin_addr); // Inet_pton

    std::cout << CLIENT << " socket create " << std::endl;

    if (connect(fd, (struct sockaddr *)&server_adr, sizeof(server_adr)) < 0)
    {
        std::cout << CLIENT_ER << " connect socket fail " << std::endl;
        exit(1);
    }
    uint32_t number_element = 4;

    File data[number_element];

    data[0].name = "delta";
    data[0].size = 1024;
    data[0].data_creation = 1111;
    data[0].number_of_links = 1;

    data[1].name = "gamma";
    data[1].size = 2048;
    data[1].data_creation = 2222;
    data[1].number_of_links = 2;

    data[2].name = "beta";
    data[2].size = 4096;
    data[2].data_creation = 3333;
    data[2].number_of_links = 3;

    data[3].name = "alfa";
    data[3].size = 8192;
    data[3].data_creation = 4444;
    data[3].number_of_links = 4;

    send(fd, &number_element, sizeof(uint32_t), 0);

    for (int i = 0; i < number_element; i++)
    {
        send(fd, &(data[i].size), sizeof(uint32_t), 0);
        send(fd, &(data[i].data_creation), sizeof(uint32_t), 0);
        send(fd, &(data[i].number_of_links), sizeof(uint32_t), 0);
    }

    for (int i = 0; i < number_element; i++)
    {

        uint32_t size_int = 0;
        size_int = htonl(data[i].name.size());

        send(fd, &size_int, sizeof(uint32_t), 0);
        send(fd, data[i].name.c_str(), data[i].name.size(), 0);
    }

    //принимаем список имен файлов в алфавитном порядке
    uint32_t number_alphabit_el = 0;
    recv(fd, &number_alphabit_el, sizeof(uint32_t), 0);
    number_alphabit_el = ntohl(number_alphabit_el);

    std::string alphabet_list[number_alphabit_el];
    RecvArrayElements(alphabet_list, number_alphabit_el, fd);

    PrintArray(alphabet_list, number_alphabit_el);

    // uint32_t size_more_than = 1024;
    // send(fd, &size_more_than, sizeof(uint32_t), 0);

    // OutPutList(alphabet_list, number_alphabit_el);

    // //принимаем список файлов больше заданного
    // uint32_t number_size_more;
    // recv(fd, &number_size_more, sizeof(uint32_t), 0);
    // std::string size_more_list[number_size_more];
    // RecvArrayElements(size_more_list, number_size_more, fd);

    // OutPutList(size_more_list, number_size_more);

    close(fd);

    return 0;
}