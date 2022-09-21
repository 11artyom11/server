/**
 * @file handler.h
 * @author Artyom Grigorian (grigorianartyom1@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-03-25
 * @section DESCRIPTION
 * This class is made to handle all incoming and outgoing
 * messages and to keep them in generic way
 * @note Handlers on server and client sides are very simlar,
 * though still it's not possible to write this class once
 * @copyright Copyright (c) 2022
 *
 * @section Last Changes 21-04-2022 Artyom Grigorian
 *
 * Improved include directories
 *
 */
#ifndef __HANDLER_H__
#define __HANDLER_H__

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <cassert>
#include <map>
#include <memory>
#include <string>

#include "constants.h"
#include "debug_helper.h"
#include "message_model.h"
#include "message_resolver.h"
#include "message_templates.h"

// Helper functor to ease cleanup of container
struct delete_ptr {
  template <typename P>
  void operator()(P p) {
    delete p;
  }
};

/**
 * @brief class to define string comparison in vector
 *
 */
class strless {
 public:
  bool operator()(const std::string& first, const std::string& second) const {
    return first < second;
  }
};

enum class CONNECT_STATE {
  conn_request,
  conn_accept,
  conn_commnd,
  conn_verify
};

struct ClientPrototype {
  std::string unique_token;
};

namespace Client {
class Handler;
/*Binding which help to add new handler functions genreically*/
typedef std::map<std::string,
                 int (Handler::*)(int, const DataTransfer::MessageModel&),
                 ::strless>
    CommMapType;

class Handler {
 public:
  Handler();
  void commap_init(void);

  int send_login_request(int sfd, const DataTransfer::MessageModel&);
  int send_connect_request(int sfd, const DataTransfer::MessageModel&);
  int on_connect_accept_recieved(int sfd, const DataTransfer::MessageModel&);
  int on_login_accept_recieved(int sfd, const DataTransfer::MessageModel&);
  int send_connect_command(int sfd, const DataTransfer::MessageModel&);
  int send_login_command(int sfd, const DataTransfer::MessageModel&);
  int send_sign_up_command(int sfd, const DataTransfer::MessageModel&);
  int on_connect_verify_recieved(int sfd, const DataTransfer::MessageModel&);
  int on_sign_up_verify_recieved(int sfd, const DataTransfer::MessageModel&);
  int on_login_verify_recieved(int sfd, const DataTransfer::MessageModel&);
  int send_terminate_connection(int sfd, const DataTransfer::MessageModel&);
  int on_broadcast_message_recieved(int sfd, const DataTransfer::MessageModel&);
  int on_chatroom_create_verified(int sfd, const DataTransfer::MessageModel&);

  CONNECT_STATE get_net_state(void) const;
  ClientPrototype const* get_client_prototype_ptr_c(void) const;

  decltype(&Client::Handler::send_connect_request) get_command(
      std::string command);

 private:
  CommMapType commap;
  /*Conciously hadn't added getter for aes token*/
  ClientPrototype cP;
  CONNECT_STATE current_state = CONNECT_STATE::conn_request;
};

}  // namespace Client
#endif /*__HANDLER_H__*/
