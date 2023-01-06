/**
 * @file message_templates.h
 * @author Artyom Grigorian (grigorianartyom1@gmail.com)
 * @brief This file is defining message templates needed
 * for the hansdshakes and customer initialization
 * @version 0.1
 * @date 2022-03-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef __MES_TEMPLATES__
#define __MES_TEMPLATES__

#include <string>

#include "../../../helpers/constants.h"
#include "message_model.h"

namespace DataTransfer {
using string = std::string;

class ConnectRequest : public MessageModel {
 public:
  ConnectRequest(const string& ip);

 private:
  static constexpr auto command = CONNECT_REQUEST;
};

class ConnectAccept : public MessageModel {
 public:
  ConnectAccept(const string& unique_token);

 private:
  static constexpr auto command = CONNECT_ACCEPT;
};

class ConnectCommand : public MessageModel {
 public:
  ConnectCommand(const string& ip, const string& unique_token);

 private:
  static constexpr auto command = CONNECT_COMMAND;
};

class ConnectVerify : public MessageModel {
 public:
  ConnectVerify(const string& enc_unique_token);

 private:
  static constexpr auto command = CONNECT_VERIFY;
};

class LoginRequest : public MessageModel {
 public:
  LoginRequest(const string& ip);

 private:
  static constexpr auto command = LOG_IN_REQUEST;
};

class LoginAccept : public MessageModel {
 public:
  LoginAccept(void);

 private:
  static constexpr auto command = LOG_IN_ACCEPT;
};

class LoginCommand : public MessageModel {
 public:
  LoginCommand(const string& name, const string& password);

 private:
  static constexpr auto command = LOG_IN_COMMAND;
};

class LoginVerify : public MessageModel {
 public:
  LoginVerify(const string& unique_token);

 private:
  static constexpr auto command = LOG_IN_VERIFY;
};

class SignUpCommand : public MessageModel {
 public:
  SignUpCommand(const string& ip, const string& name, const string& dial,
                const string& email, const string& passwd);

 private:
  static constexpr auto command = SIGN_UP_COMMAND;
};

class SignUpVerify : public MessageModel {
 public:
  SignUpVerify(const string& unqiue_token);

 private:
  static constexpr auto command = SIGN_UP_VERIFY;
};

class BroadcastMessage : public MessageModel {
 public:
  BroadcastMessage(const string& message, const string& trigger_token,
                   const string& room_id, const string& name);

 private:
  static constexpr auto command = BRDCST_MESSAGE_COMMAND;
};

class CreateChatroomVerify : public MessageModel {
 public:
  CreateChatroomVerify(const std::string& new_room_id, const std::string& owner_id);

 private:
  static constexpr auto command = CHATROOM_CREATE_VERIFY;
};

class JoinChatroomCommand : public MessageModel {
  public:
    JoinChatroomCommand(const std::string& room_id, const std::string& master_token, const std::string& utoken);
  private:  
    static constexpr auto command = JOIN_CHATROOM_COMMAND;
};

class ChatroomJoinedCustomer : public MessageModel{
  public:
    ChatroomJoinedCustomer(const std::string& cust_id, const std::string& owner_id, const std::string& room_id);
  private:
    static constexpr auto command = CHATROOM_JOINED_CUSTOMER;

};

class SafeMessageModel : public MessageModel {
 public:
  /* This c-tor is deleted because in this class safe field MUST contain cipher
   * of Basic MessageModel */
  SafeMessageModel(const std::string& crpt_hex, int crpt_len);
  SafeMessageModel(const DataTransfer::MessageModel&) = delete;
  static std::string makeSafeMessage(const std::string& crpt_hex, int crpt_len);
};

}  // namespace DataTransfer

#endif /*__MES_TEMPLATES*/