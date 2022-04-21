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
 * @section Last Changes 21-04-2022 Artyom Grigorian
 *
 * Improved include directories
 *  
 */

#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "connection_handler.h"
#include "communication_unit.h"
#include "constants.h"
#include "debug_helper.h"

#include <memory>
#include <utility>


namespace Client{
    template <typename T>
    using shared_ptr = std::shared_ptr<T>;

    template <typename T>
    using unique_ptr = std::unique_ptr<T>;
    
    typedef shared_ptr <Net::BasicConnectionHandler> \
            BasicConnectionHandlerSharedPtr;

    typedef shared_ptr <Net::BasicCommunicationModel> \
            BasicCommunicationModelSharedPtr;

    class ClientModel
    {
        public:
            ClientModel(int __port = DEFAULT_PORT);
            int connect_to_default_host (void);
            ~ClientModel();
        private:    
            BasicConnectionHandlerSharedPtr con_handler;
            BasicCommunicationModelSharedPtr comm_unit;

    };
};

#endif
