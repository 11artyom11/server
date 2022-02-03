#ifndef __CLIENT_H__
#define __CLIENT_H__
#include "connection_handler.h"
#include "../../../lib/include/helpers/constants.h"
#include "../../../lib/include/helpers/debug_helper/debug_helper.h"

namespace Client{
    class ClientModel
    {
        public:
            ClientModel(int __port = DEFAULT_PORT);
            ~ClientModel();
        private:    
            Net::BasicConnectionHandler* con_handler;

    };
};

#endif
