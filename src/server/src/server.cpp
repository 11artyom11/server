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
Server::ServerModel::ServerModel(uint32_t port) :
    listen_port {port},
        protocol_family {AF_INET},
            listen_ip {INADDR_ANY},
                m_handler {3}

{

    Debug().info("Constructed ServerModel instance");

    server_addr = new struct sockaddr_in;

    server_addr->sin_port = htons(listen_port);
    server_addr->sin_family = protocol_family;
    server_addr->sin_addr.s_addr = listen_ip;
}

/**
 * @brief sets working port on which server will be listening to
 * 
 * @param port 
 * @return true if succeed to set listen port else false
 */
bool Server::ServerModel::set_server_port(uint16_t port)
{
    Debug().info("Server port set to ", port);
    std::string debugMes = "Set server port to " +  ( port + '0');
    server_addr->sin_port = htons(port);
    //Debug() << std::string{debugMes};
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
    Debug().info("Server protocol family set to ", family);
    std::string debugMes = "Set protocol family to " + (family + '0');
    //Debug() << std::string{debugMes};
    server_addr->sin_family = family;
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
    Debug().info("Server listen ip set to ", ip);
    std::string debugMes = "Set listen ip to " + (ip + '0');
    //Debug() << std::string{debugMes};
    server_addr->sin_addr.s_addr = htons(ip);
    this->listen_ip = ip;
    return true;
}


/**
 * @brief bind socket file descriptor to server address
 * 
 * @param sockfd 
 * @return On success, zero is returned.  On error, -1 is returned, and
       errno is set to indicate the error. 
 */
int Server::ServerModel::bind_client_socket(int sockfd)
{
    /*for more info see https://man7.org/linux/man-pages/man2/bind.2.html*/
    return bind(sockfd, 
                   reinterpret_cast<sockaddr*>(this->server_addr), 
                        sizeof(*server_addr));
}

/**
 * @brief Prepare to accept connections on socket FD.
N connection requests will be queued before further requests are refused.
Returns 0 on success, -1 for errors.
 * 
 * @param sockfd 
 * @param pending_connection_quantity 
 * @return Returns 0 on success, -1 for errors. 
 */
int Server::ServerModel::listen_to_socket(int sockfd, 
                                            uint32_t pending_connection_quantity)
{
    return listen (sockfd, pending_connection_quantity);
}

/**
 * @brief Await a connection on socket FD.
When a connection arrives, open a new socket to communicate with it,
set *ADDR (which is *ADDR_LEN bytes long) to the address of the connecting
peer and *ADDR_LEN to the address's actual length. r
 * 
 * @param sockfd 
* @return   Returns  the
            new socket's descriptor, or -1 for errors
 */
int Server::ServerModel::accept_connection_from_socket (int sockfd)
{
    socklen_t size = sizeof (*this->server_addr);
    return accept (sockfd, 
                    reinterpret_cast<sockaddr*>(this->server_addr),
                        &size);
}


void Server::ServerModel::dump_server_state(void) const noexcept
{
    Debug().info("Server listen address : ",server_addr->sin_addr.s_addr);
    Debug().info("Server listen port : ", server_addr->sin_port, "(", listen_port, ")");
    Debug().info("Server protocol family : ",server_addr->sin_family);
    return;
}

/**
 * @brief Returns set upped server address struct
 * 
 * @return struct sockaddr_in* 
 */
struct sockaddr_in* Server::ServerModel::get_server_addr() const
{
    return this->server_addr;
}


void Server::ServerModel::distribute_incoming_connections(int new_socket, 
                                                                uint8_t response)
{
    switch (response)
    {
    case WRITE_REQ:
        Debug().info("Got WRITE ORDER");
        m_handler.provide_write_thread(new_socket);
        break;
    
    case READ_REQ:
        Debug().info("Got READ ORDER");
        m_handler.provide_read_thread(new_socket);
        break;
    default: 
        return;
    }
}


/**
 * @brief Destroy the Server:: Server Model:: Server Model object
 * 
 */
Server::ServerModel::~ServerModel()
{
    delete server_addr;
    Debug().info("Destructed Server Model object");
}

/**
 * create sockete
 * bind with ip and port 
 * listen socket to port 
 * accept messages
 * 
 */