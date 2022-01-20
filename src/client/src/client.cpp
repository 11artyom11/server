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

constexpr auto DEFAULT_PORT = 9982;
constexpr auto BUFFER_SIZE = 1024; 
constexpr auto SERVER_IP = "127.0.0.1";
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
                   MACHINE_TYPE m_type = MACHINE_TYPE::CLIENT )
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



int main(int agrc, char* argv[])
{
    int client;
    struct sockaddr_in server_address;
    client = socket (AF_INET, SOCK_STREAM, 0);
    if (client < 0)
    {
        debug ("Socket establishing error", DEBUG_TYPE::ERROR_T);
        exit(0);
    }
    server_address.sin_port = htons(DEFAULT_PORT);
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr);

    debug("CLient socket creatd");

    int ret  = connect (client, 
                    reinterpret_cast<const struct sockaddr*> (&server_address),
                        sizeof(server_address));
    if (ret == 0)
    {
        debug ("Connected to server ");    
    }

    char buffer[BUFFER_SIZE];

    debug ("Waiting for server confirmation");
    recv(client, buffer,BUFFER_SIZE, 0);
    debug (buffer); 
    debug ("Connection established");
    debug ("Enter # to close connection");

    while (true)
    {
        std::cin.getline (buffer, BUFFER_SIZE);
        debug (buffer);
        send (client, buffer, BUFFER_SIZE, 0);\
        if (is_client_connection_close(buffer))
        {
            break;
        }
        recv(client, buffer, BUFFER_SIZE, 0);
        debug (buffer, DEBUG_TYPE::INFO_T, MACHINE_TYPE::SERVER);
        if (is_client_connection_close(buffer))
        {
            break;
        }

    }
    close(client);
    debug ("Connection terminated");

    return 0;
}