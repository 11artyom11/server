/**
 * @file client.h
 * @author Artyom Grigorian (girogrianartyom1@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-20
 * 
 * @section DESCRIPTION
 * This ClientModel class represents Client main API interface 
 * to deal with remote clients and store local (server) data
 * Is defined in Client namespace
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __CLIENT_H__
#define __CLIENT_H__
#include "connection_handler.h"
#include "communication_unit.h"
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
            Net::BasicCommunicationModel* comm_unit;

    };
};

#endif
