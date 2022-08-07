/**
 * @file message_resolver.h
 * @author Artyom Grigorian (grigorianartyom1@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-03-20
 * @section DESCRIPTION
 * This class is made to provide Formatters for inputted data, and
 * turn string literals into transferable data model , and so on.
 * Is defined in DataTransfer namespace
 * @copyright Copyright (c) 2022
 *
 */
#ifndef __MESSAGE_RESOLVER_H__
#define __MESSAGE_RESOLVER_H__

#include <algorithm>
#include <any>
#include <map>
#include <string>

#include "../message_model/message_model.h"

using string = std::string;
// using  std::map           = std::std::map;
using JsonValType = std::any;

namespace DataTransfer {
enum class COMMAND_NAME {
  LOG_IN_REQUEST,
  CONNECT_REQUEST,

  LOG_IN_ACCEPT,
  CONNECT_ACCEPT,

  CONNECT_COMMAND,
  SIGN_UP_COMMAND,
  LOG_IN_COMMAND,
  WRITE_COMMAND,
  READ_COMMAND,
  EXIT_COMMAND,

  SIGN_UP_VERIFY,
  LOG_IN_VERIFY,
  CONNECT_VERIFY
};

/**
 * @brief This class is designed to support instant
 * message template support via helper functions
 *
 */

class MessageResolver {
 public:
  MessageResolver();
  MessageModel distribute_command(const std::map<string, JsonValType>&,
                                  COMMAND_NAME cN) const;

  MessageModel init_log_in_message(
      const std::map<string, JsonValType>&) const __THROW;

  MessageModel init_sign_up_message(
      const std::map<string, JsonValType>&) const __THROW;

  ~MessageResolver();
};

bool is_message_initial_data_valid(COMMAND_NAME cN,
                                   const std::map<string, JsonValType>&);

bool is_message_valid(MessageModel& mModel);

COMMAND_NAME get_command_from_s(std::string command);
}  // namespace DataTransfer

#endif  //__MESSAGE_RESOLVER_H__
