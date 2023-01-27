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
 * @section Last Changes 21-04-2022 Artyom Grigorian
 *
 * Improved include directories
 *
 */
#ifndef __CONNECTION_HANDLER_H__
#define __CONNECTION_HANDLER_H__
#define SA struct sockaddr

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

namespace Net {
template <typename T>
using shared_ptr = std::shared_ptr<T>;

template <typename T>
using unique_ptr = std::unique_ptr<T>;
using sockaddr_in_unq_ptr = unique_ptr<struct sockaddr_in> ;

class BasicConnectionHandler {
 public:
  BasicConnectionHandler();
  // BasicConnectionHandler(const BasicConnectionHandler&) = delete;
  ~BasicConnectionHandler();

  int get_sockfd(void) const noexcept;
  struct sockaddr_in* get_sockaddr(void) const noexcept;

  bool setup_socket(int __domain, int __type, int __protocol);
  bool setup_server_addr(int __family, std::string __host, uint32_t __port);

  bool set_server_addr(struct sockaddr_in* new_serv_addr);

 private:
  /*Main connection socket file descriptior*/
  int m_connection;
  sockaddr_in_unq_ptr server_addr;
};

bool connect_to_host(const BasicConnectionHandler& basic_CH);

};  // namespace Net

#endif
