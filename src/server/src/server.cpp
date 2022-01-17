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
 * create sockete
 * bind with ip and port 
 * listen socket to port 
 * accept messages
 * 
 */