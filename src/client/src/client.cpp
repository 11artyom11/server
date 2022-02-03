#include "../include/client.h"

using namespace Client;
using namespace Net;

ClientModel::ClientModel(int __port)
{
    con_handler = new BasicConnectionHandler();
    bool sock_res = con_handler->setup_socket(AF_INET, SOCK_STREAM, 0);
    bool serv_res = con_handler->setup_server_addr(AF_INET, SERVER_IP, __port);
    if (!(sock_res & serv_res))
    {
        Debug().fatal("Failed to create socket. terminating...");
        exit(0);
    }
    int connect_result = connect_to_host(*con_handler);
    if (!connect_result)
    {
        Debug().fatal("Failed to connect to host, ... terminating...");
    }
}

ClientModel::~ClientModel()
{

}