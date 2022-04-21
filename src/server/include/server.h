/**
 * @file server.h
 * @author Artyom Grigorian (grigorianartyom1@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-20
 * @section DESCRIPTION 
 * This class is made to provide high level server API's 
 * This class calls corresponding functions and runs commands to 
 * handle particular client-side request
 * Is defined in Server namespace
 * 
 * @section Last Changes 2022-03-21 Artyom Grigorian
 * Changed Handler instance to Handler smart pointer
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __SERVER__
#define __SERVER__

#include "../../../lib/include/helpers/debug_helper/debug_helper.h"
#include "../../../lib/include/util/data_transfer/message_model/message_model.h"
#include "../../../lib/include/util/data_transfer/message_resolver/message_resolver.h"

#include "handler.h"

#include <iostream>
#include <string>
#include <cstring>
#include <memory>
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
    template <typename T>
    using unique_ptr = std::unique_ptr<T>;

      

    typedef unique_ptr<Handler> \
                Handler_unq_ptr;

    typedef unique_ptr<struct sockaddr_in> \
            sockaddr_in_unq_ptr;



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
            int distribute_incoming_connections     (int new_socket, char* response);
            void handle_connection                  (int connection);
            /*Generate and assign RSA keypair for server side*/
            int init_server_keypair (char* passphrase = nullptr);

            /*Set already existing RSA_Keypair (typedef) to model*/
            int set_server_keypair (const Security::RSA_Keypair& __other);

            /*Return RSA_Keypair of $this model*/
            Security::RSA_Keypair const * get_server_keypair (void);


            ~ServerModel                            ();

        
        private:
            static int          connected_users_count;
            static int          pending_connections_count;
            std::vector <int>   sockfds;
            

        private:
        /* Structure describing an Internet socket address.  */
            sockaddr_in_unq_ptr  server_addr;

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
            Handler_unq_ptr m_handler;
            Security::RSA_Keypair_shrd_ptr keypair;
        
    };

}

#endif //__SERVER__