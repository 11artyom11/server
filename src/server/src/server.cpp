#include "../include/server.h"

bool Server::is_client_connection_close(const char* msg)
{
    for (int i = 0; i < strlen (msg); ++i)
    {
        if (msg[i] == EXIT_SYM)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Construct a new Server:: Server Model object =>
 *  default constructor
 * 
 */
Server::ServerModel::ServerModel()
{
    Debug("Constructed Server Model object");
}

/**
 * @brief sets working port on which server will be listening to
 * 
 * @param port 
 * @return true if succeed to set listen port 
 * @return false if failed to set listen port
 */
bool Server::ServerModel::set_server_port(uint16_t port)
{
    std::string debugMes = "Set server port to " +  ( port + '0');
    Debug(std::string{debugMes});
    this->listen_port = port;
    return true;
}

/**
 * @brief sets working protocol family (ipV4 as default)
 * 
 * @param family 
 * @return true if succeed to set protocol family
 * @return false if failed to set protocol family
 */
bool Server::ServerModel::set_protocol_family(uint16_t family)
{
    std::string debugMes = "Set protocol family to " + (family + '0');
    Debug(std::string{debugMes});
    this->protocol_family = family;
    return true;
}

/**
 * @brief Sets ip on which server will be listening to 
 *  (INADDR_ANY (default parameter) means server will listen to all pending addresses)
 * 
 * @param ip 
 * @return true if succeed to set listen ip
 * @return false if failed to set listen ip
 */
bool Server::ServerModel::set_listen_ip(in_addr_t ip)
{
    std::string debugMes = "Set listen ip to " + (ip + '0');
    Debug(std::string{debugMes});
    this->listen_ip = ip;
    return true;
}


/**
 * @brief bind socket file descriptor to server address
 * 
 * @param sockfd 
 * @return int 
 * @return On success, zero is returned.  On error, -1 is returned, and
       errno is set to indicate the error. 
 */
int Server::ServerModel::bind_client_socket(int sockfd)
{
    /*for more info see https://man7.org/linux/man-pages/man2/bind.2.html*/
    return bind(sockfd, 
                   reinterpret_cast<sockaddr*>(&this->server_addr), 
                        sizeof(server_addr));
}



/**
 * @brief Destroy the Server:: Server Model:: Server Model object
 * 
 */
Server::ServerModel::~ServerModel()
{
     Debug("Destructed Server Model object");
}

/**
 * create sockete
 * bind with ip and port 
 * listen socket to port 
 * accept messages
 * 
 */