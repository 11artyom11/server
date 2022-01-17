#include "../include/server.h"

using namespace Server;

int main(int argc, char* argv[])
{

    int client;
    int server;


    struct sockaddr_in server_address;
    client = socket (AF_INET, SOCK_STREAM,0);
    if (client < 0)
    {
        Debug("Socket cannot be established", DEBUG_TYPE::ERROR_T);
        exit(0);
    }


    Debug("Socket for server was created");    
    server_address.sin_port = htons(DEFAULT_PORT);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htons (INADDR_ANY);

    int ret  = bind(client,
                         reinterpret_cast<struct sockaddr*>(&server_address),
                                sizeof(server_address));


    if (ret < 0)
    {
        Debug("binding connection... Socket has already been establishing",DEBUG_TYPE::ERROR_T);
        exit(0);
    }

    socklen_t size = sizeof (server_address);

    Debug("Server is listening...");

    listen(client, 1);
    server = accept (client, reinterpret_cast<struct sockaddr*>(&server_address), &size);
    
    if (server < 0)
    {
        Debug("Couldn't accept client", DEBUG_TYPE::ERROR_T);
    }

    char buffer[BUFFER_SIZE];
    bool isExit = false;
    while (server > 0)
    {
        strcpy (buffer, "Server connected ...\n");
        send (server, buffer, BUFFER_SIZE, 0);

         
        
        Debug ("Connected to client #1\nEnter \'#\' to end connection");

       
        recv(server, buffer, BUFFER_SIZE, 0);
        Debug(buffer,DEBUG_TYPE::INFO_T, MACHINE_TYPE::CLIENT);
        
        if (is_client_connection_close(buffer))
        {
            isExit = true;
        }
        while (!isExit)
        {
            Debug ("");
            std::cin.getline(buffer, BUFFER_SIZE);
            send(server, buffer, BUFFER_SIZE, 0);
            if (is_client_connection_close(buffer))
            {
                break;
            }

            recv (server, buffer, BUFFER_SIZE, 0);
            Debug(buffer,DEBUG_TYPE::INFO_T,MACHINE_TYPE::CLIENT);
            if (is_client_connection_close(buffer))
            {
                break;
            }
        }
        Debug ("Client disconnected");
        isExit = false;
        exit(1);
    }

    exit(0);
}