#ifndef __SERVER__
#define __SERVER__
#include "../../../lib/include/helpers/debug_helper/debug_helper.h"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

namespace Server
{
    bool is_client_connection_close(const char* msg);

    class ServerModel
    {
        public:
            ServerModel();
            ~ServerModel();

        
        private:
            static int connected_users;
            static int pending_connections;
            std::vector <int> sockfds;
            //for test commit

    };

}

#endif //__SERVER__