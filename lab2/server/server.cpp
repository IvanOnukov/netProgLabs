#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
// #include "../lib/errproc.h"
#include "../lib/struct.cpp"

#define DEFAULT_PORT 47999
#define ERROR_S "SERVER ERROR: "
#define SERVER "SERVER: "
#define buffer_size 1024

void ShortByAlphabet(std::string *source_array, const int &array_size)
{
    for (int i = 0; i < array_size - 1; i++)
    {
        for (int j = 0; j < array_size - 1; j++)
        {
            if (source_array[j] > source_array[j + 1])
            {
                std::string swp_var = source_array[j];
                source_array[j] = source_array[j + 1];
                source_array[j + 1] = swp_var;
            }
        }
    }
}

void SendArrayElements(std::string *sourse_array, uint32_t &array_size, int fd)
{
    array_size = htonl(array_size);
    send(fd, &array_size, sizeof(uint32_t), 0);
    array_size = ntohl(array_size);

    for (int i = 0; i < array_size; i++)
    {
        uint32_t size_el = sourse_array[i].size();
        size_el = htonl(size_el);

        send(fd, &size_el, sizeof(uint32_t), 0);
        send(fd, sourse_array[i].c_str(), sourse_array[i].size(), 0);
    }
}

void  PrintArray(std::string *source_array, const int &array_size)
{
    for (int i = 0; i < array_size; i++)
    {
        std::cout << source_array[i] << "\t";
    }
    std::cout << std::endl;
}

int main()
{
    int client;
    int server;

    struct sockaddr_in server_adr;

    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client < 0)
    {
        std::cout << ERROR_S << "conect  socket error" << std::endl;
        exit(1);
    }

    std::cout << "SERVER: create socket " << std::endl;

    server_adr.sin_family = AF_INET;
    server_adr.sin_port = htons(DEFAULT_PORT);
    server_adr.sin_addr.s_addr = htonl(INADDR_ANY);

    int ret = bind(client,
                   reinterpret_cast<struct sockaddr *>(&server_adr),
                   sizeof(server_adr));

    if (ret == -1)
    {
        std::cout << ERROR_S << " bind error " << std::endl;
        exit(2);
    }

    std::cout << SERVER << "Litenung client ..." << std::endl;
    listen(client, 1);

    socklen_t size = sizeof(server_adr);

    server = accept(client, reinterpret_cast<struct sockaddr *>(&server_adr), &size);
    if (server < 0)
    {
        std::cout << ERROR_S << "accept error" << std::endl;
    }

    uint32_t number_send_element;
    recv(server, &number_send_element, sizeof(uint32_t), 0);

    File send_data[number_send_element];

    for (int i = 0; i < number_send_element; i++)
    {
        recv(server, &(send_data[i].size), sizeof(uint32_t), 0);
        recv(server, &(send_data[i].data_creation), sizeof(uint32_t), 0);
        recv(server, &(send_data[i].number_of_links), sizeof(uint32_t), 0);
    }

    uint32_t size_int;
    for (int i = 0; i < number_send_element; i++)
    {
        recv(server, &size_int, sizeof(uint32_t), 0);
        size_int = ntohl(size_int);

        char bufer_name[size_int];

        recv(server, &(bufer_name), size_int, 0);

        send_data[i].name.assign(bufer_name, sizeof(bufer_name));
    }

    for (int i = 0; i < number_send_element; i++)
    {
        std::cout << send_data[i].name << std::endl;
        std::cout << send_data[i].size << std::endl;
        std::cout << send_data[i].data_creation << std::endl;
        std::cout << send_data[i].number_of_links << std::endl;
    }

    std::string array_names[number_send_element];
    for (int i = 0; i < number_send_element; i++)
    {
        array_names[i] = send_data[i].name;
    }

    //отправка списка имен отсортированых по алфавиту
    ShortByAlphabet(array_names, number_send_element);
  
    PrintArray(array_names, number_send_element);




    SendArrayElements(array_names, number_send_element, client);

    // uint32_t number_compare;
    // recv(server, &number_compare, sizeof(uint32_t), 0);

    // uint32_t count = 0;
    // for (int i = 0; i < number_send_element; i++)
    // {
    //     if (send_data[i].size > number_compare)
    //         count++;
    // }

    // if (count == 0)
    // {
    //     std::cout << ERROR_S << "не найдено подходяших размеров файлов" << std::endl;
    //     exit(3);
    // }

    // std::string array_size[count];
    // int it = 0;
    // for (int i = 0; i < number_send_element; i++)
    // {
    //     if (send_data[i].size > number_compare)
    //     {
    //         array_size[it] = send_data[i].size;
    //         it++;
    //     }
    // }

    // SendArrayElements(array_names, count, client);

    close(server);
    close(client);

    return 0;
}
