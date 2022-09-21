/**
 * @file customer.h
 * @author Artyom Grigorian (grigorianartyom1@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-03-23
 * @section DESCRIPTION
 * This class is made to add abstract level to customer
 * model on server side
 *
 * @section Last Changes 21-04-2022 Artyom Grigorian
 *
 * Improved include directories
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef __CUSTOMER_H__
#define __CUSTOMER_H__
#include <sys/socket.h>

#include <algorithm>
#include <memory>
#include <random>
#include <string>

#include "message_model.h"
#include "message_templates.h"

enum class CONNECT_STATE {
  conn_request,
  conn_accept,
  conn_commnd,
  conn_verify
};

namespace Customer {
template <typename T>
using shared_ptr = std::shared_ptr<T>;

class CustomerModel {
 public:
  CustomerModel(int sfd, const std::string& unique_token);
  ~CustomerModel();
  int get_sfd(void) const noexcept;
  std::string get_unique_token(void) const noexcept;

  void send_message(const DataTransfer::MessageModel&);

 public:
  CONNECT_STATE current_state = CONNECT_STATE::conn_request;

 private:
  /* To access cipher unit of customer */
  std::string unique_token;
  int sfd;
};
};  // namespace Customer

#endif  //__CUSTOMER_H__