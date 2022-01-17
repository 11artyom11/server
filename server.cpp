#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

constexpr auto SERVER_NAME = "=> [SERVER] ";
constexpr auto CLIENT_NAME = "=> [CLIENT] ";

constexpr auto ERROR_S = "[ERROR] : "; 
constexpr auto INFO_S = "[INFO] : ";
constexpr auto WARNING_S = "[WARNING] : ";

constexpr auto DEFAULT_PORT = 8080;
constexpr auto BUFFER_SIZE = 1024; 
constexpr auto EXIT_SYM = '#';

enum class DEBUG_TYPE
{
    ERROR_T,
    INFO_T,
    WARNING_T
};

enum class MACHINE_TYPE
{
    SERVER,
    CLIENT
};

template <typename MES_t>
void debug(const MES_t& message,
                DEBUG_TYPE d_type = DEBUG_TYPE::INFO_T,
                   MACHINE_TYPE m_type = MACHINE_TYPE::SERVER )
{
    std::string who{};
    std::string carriage_head{};
    switch (m_type)
    {
    case MACHINE_TYPE::SERVER:
        who = SERVER_NAME;
        break;
    
    case MACHINE_TYPE::CLIENT:
        who = CLIENT_NAME;
        break;
    }

    switch (d_type)
    {
    case DEBUG_TYPE::ERROR_T:    
        carriage_head = ERROR_S;
        break;
    
    case DEBUG_TYPE::INFO_T:
        carriage_head = INFO_S;
        break;
    case DEBUG_TYPE::WARNING_T:
        carriage_head = WARNING_S;
        break;
    }
    std::cerr << who <<  carriage_head << message << '\n';
}


bool is_client_connection_close(const char* msg)
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


int main(int argc, char* argv[])
{
    int client;
    int server;


    struct sockaddr_in server_address;
    client = socket (AF_INET, SOCK_STREAM,0);
    if (client < 0)
    {
        debug("Socket cannot be established", DEBUG_TYPE::ERROR_T);
        exit(0);
    }


    debug("Socket for server was created");    
    server_address.sin_port = htons(DEFAULT_PORT);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htons (INADDR_ANY);

    int ret  = bind(client,
                         reinterpret_cast<struct sockaddr*>(&server_address),
                                sizeof(server_address));


    if (ret < 0)
    {
        debug("binding connection... Socket has already been establishing",DEBUG_TYPE::ERROR_T);
        exit(0);
    }

    socklen_t size = sizeof (server_address);

    debug("Server is listening...");

    listen(client, 1);
    server = accept (client, reinterpret_cast<struct sockaddr*>(&server_address), &size);
    
    if (server < 0)
    {
        debug("Couldn't accept client", DEBUG_TYPE::ERROR_T);
    }

    char buffer[BUFFER_SIZE];
    bool isExit = false;
    while (server > 0)
    {
        strcpy (buffer, "Server connected ...\n");
        send (server, buffer, BUFFER_SIZE, 0);

         
        
        debug ("Connected to client #1\nEnter \'#\' to end connection");

       
        recv(server, buffer, BUFFER_SIZE, 0);
        debug(buffer,DEBUG_TYPE::INFO_T, MACHINE_TYPE::CLIENT);
        
        if (is_client_connection_close(buffer))
        {
            isExit = true;
        }
        while (!isExit)
        {
            debug ("");
            std::cin.getline(buffer, BUFFER_SIZE);
            send(server, buffer, BUFFER_SIZE, 0);
            if (is_client_connection_close(buffer))
            {
                break;
            }

            recv (server, buffer, BUFFER_SIZE, 0);
            debug(buffer,DEBUG_TYPE::INFO_T,MACHINE_TYPE::CLIENT);
            if (is_client_connection_close(buffer))
            {
                break;
            }
        }
        debug ("Client disconnected");
        isExit = false;
        exit(1);
    }

    exit(0);
}

/**
 * create sockete
 * bind with ip and port 
 * listen socket to port 
 * accept messages
 * 
 */