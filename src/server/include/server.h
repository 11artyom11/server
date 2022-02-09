#ifndef __SERVER__
#define __SERVER__

#include "../../../lib/include/helpers/debug_helper/debug_helper.h"
#include "../../../lib/include/util/cyptolib/crypto_unit.h"

#include "handler.h"

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

/*Namespace purposed to store server-related functions and classes*/
namespace Server
{
    bool is_client_connection_close(const char* msg);

    class ServerModel
    {
        public:
            ServerModel                             (uint32_t port = DEFAULT_PORT);
            bool set_server_port                    (uint16_t port = DEFAULT_PORT);
            bool set_protocol_family                (uint16_t family = AF_INET);
            bool set_listen_ip                      (in_addr_t ip = INADDR_ANY);
            int bind_client_socket                  (int sockfd);
            int listen_to_socket                    (int sockfd, uint32_t pending_connection_quantity = 1);
            int accept_connection_from_socket       (int sockfd);
            void dump_server_state                  (void) const noexcept;
            struct sockaddr_in* get_server_addr     () const;
            void distribute_incoming_connections    (int new_socket, uint8_t response);

            ~ServerModel             ();

        
        private:
            static int          connected_users_count;
            static int          pending_connections_count;
            std::vector <int>   sockfds;
            

        private:
        /* Structure describing an Internet socket address.  */
            struct sockaddr_in*  server_addr;

        /*variable (int) that stores port server listens to  in host byte order*/
            uint16_t            listen_port;

        /*
            variable (int) that stores protocol family via which client
            server communication is being done
        */
            int                 protocol_family;

        /*Ip from which connection requests are being accepted
            uint32_t*/
            in_addr_t           listen_ip;

        /*Handler for write and read functions*/
            Handler m_handler;

    };

}

#endif //__SERVER__