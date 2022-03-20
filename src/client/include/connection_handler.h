/**
 * @file connection_handler.h
 * @author Artyom Grigorian (grigorianartyom1@gmail.com)
 * @version 0.1
 * @date 2022-03-20
 * @section DESCRIPTION
 * This class is made to establish stable connection 
 * between server and remote node (client)
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __CONNECTION_HANDLER_H__
#define __CONNECTION_HANDLER_H__
#define SA struct sockaddr

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <mutex>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

namespace Net
{
    class BasicConnectionHandler
    {
        public:
            BasicConnectionHandler();
            ~BasicConnectionHandler();

            int get_sockfd      (void) const noexcept;
            struct sockaddr_in* get_sockaddr    (void) const noexcept;

            bool setup_socket   (int __domain, 
                                    int __type, 
                                        int __protocol);
            bool setup_server_addr (int __family,
                                        std::string __host,
                                            uint32_t __port);

            bool set_server_addr (struct sockaddr_in* new_serv_addr);
                        

        private:
        /*Main connection socket file descriptior*/
            int  m_connection;
            struct sockaddr_in*  server_addr;
            

    };

    bool connect_to_host (const BasicConnectionHandler& basic_CH);
        
};

#endif
