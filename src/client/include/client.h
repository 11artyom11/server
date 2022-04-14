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
 * @section Last Changes 2022-03-21
 * @section Summary
 * Changed all pure pointers into smart pointers in order to avoid
 * unintended memleaks around this file
 */

#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "connection_handler.h"
#include "communication_unit.h"
#include "../../../lib/include/helpers/constants.h"
#include "../../../lib/include/helpers/debug_helper/debug_helper.h"

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
