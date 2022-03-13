#include "../include/client.h"

using namespace Client;
using namespace Net;

ClientModel::ClientModel(int __port)
{
    con_handler = new BasicConnectionHandler();
    comm_unit = new BasicCommunicationModel();
    
    bool sock_res = con_handler->setup_socket(AF_INET, SOCK_STREAM, 0);
    bool serv_res = con_handler->setup_server_addr(AF_INET, SERVER_IP, __port);
    int main_socket = con_handler->get_sockfd();
    
    
    if (!(sock_res & serv_res))
    {
        Debug().fatal("Failed to create socket. terminating...");
        exit(0);
    }
    int connect_result = connect_to_host(*con_handler);
    if (!connect_result)
    {
        Debug().fatal("Failed to connect to host, ... terminating...");
        exit(0);
    }

   
   auto read_th = std::async(std::launch::async ,&Net::BasicCommunicationModel::start_read_async, this->comm_unit, main_socket);
   auto write_th = std::async(std::launch::async, &Net::BasicCommunicationModel::start_write_async, this->comm_unit, main_socket, std::ref(std::cin));

    Debug().info("Out of Client Model C-tor");

}

ClientModel::~ClientModel()
{

}