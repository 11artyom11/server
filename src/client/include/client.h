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

#include <memory>
#include <utility>

#include "communication_unit.h"
#include "connection_handler.h"
#include "constants.h"
#include "debug_helper.h"

namespace Client {
template <typename T>
using shared_ptr = std::shared_ptr<T>;

template <typename T>
using unique_ptr = std::unique_ptr<T>;

typedef shared_ptr<Net::BasicConnectionHandler> BasicConnectionHandlerSharedPtr;

typedef shared_ptr<Net::BasicCommunicationModel>
    BasicCommunicationModelSharedPtr;

class ClientModel {
 public:
  ClientModel(void);
  ClientModel(int __port);
  void init_new_client(int __port);
  int connect_to_default_host(void);
  int get_connection_state(void) const noexcept;
  BasicConnectionHandlerSharedPtr get_con_handler(void) const noexcept;
  BasicCommunicationModelSharedPtr get_comm_unit(void) const noexcept;
  int send_to_host(const DataTransfer::MessageModel&);
  int send_join_to_room_request(const std::string& master_token,
                                const std::string& room_id);
  int close_connection(void);
  ~ClientModel();

 private:
  BasicConnectionHandlerSharedPtr con_handler;
  BasicCommunicationModelSharedPtr comm_unit;
  /* enum telling connection between client and server */
  /* don't mess with net_state in handler unit  */
  int connection_state = -1;
  int main_socket;
};
};  // namespace Client

#endif
