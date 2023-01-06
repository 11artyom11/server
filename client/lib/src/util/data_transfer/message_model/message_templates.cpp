#include "../../../../include/util/data_transfer/message_model/message_templates.h"

using namespace DataTransfer;

ConnectRequest::ConnectRequest(const string& ip) {
  Debug().info("Constructed ConnectRequest Message");
  this->set("command", this->command);
  this->set("ip", ip);
}

ConnectAccept::ConnectAccept(const string& unique_token) {
  Debug().info("Constructed ConnectAccept Message");
  this->set("command", this->command);
  this->set("unique_token", unique_token);
}

ConnectCommand::ConnectCommand(const string& ip, const string& unique_token) {
  Debug().info("Constructed ConnectCommand Message");
  this->set("command", command);
  this->set("ip", ip);
  this->set("unique_token", unique_token);
}

ConnectVerify::ConnectVerify(const string& unique_token) {
  Debug().info("Constructed ConnectVerify Message");
  this->set("command", command);
  this->set("unique_token", unique_token);
}

LoginRequest::LoginRequest(const string& ip) {
  Debug().info("Constructed LoginRequest Message");
  this->set("command", command);
  this->set("ip", ip);
}

LoginAccept::LoginAccept(void) {
  Debug().info("Constructed LoginAccept Message");
  this->set("command", command);
}

LoginCommand::LoginCommand(const string& name, const string& password) {
  Debug().info("Constructed LoginCommand Message");
  this->set("command", command);
  this->set("name", name);
  this->set("passwd", password);
}

LoginVerify::LoginVerify(const string& unique_token) {
  Debug().info("Constructed LoginVerify Message");
  this->set("command", command);
  this->set("perm_uid", unique_token);
}

SignUpCommand::SignUpCommand(const string& ip, const string& name,
                             const string& dial, const string& email,
                             const string& passwd) {
  Debug().info("Constructed SignUpCommand Message");
  this->set("command", command);
  this->set("ip", ip);
  this->set("name", name);
  this->set("dial", dial);
  this->set("email", email);
  this->set("passwd", passwd);
}

SignUpVerify::SignUpVerify(const string& unique_token) {
  Debug().info("Constructed SignUpVerify Message");
  this->set("command", command);
  this->set("perm_uid", unique_token);
}

BroadcastMessage::BroadcastMessage(const string& message,
                                   const string& trigger_token,
                                   const string& room_id, const string& name) {
  Debug().info("Constructed BroadcastMessage Message");
  this->set("command", command);
  this->set("message", message);
  this->set("trg_token", trigger_token);
  this->set("room_id", room_id);
  this->set("name", name);
}

CreateChatroomCommand::CreateChatroomCommand(void){
  this->set("command", command);
}

CreateChatroomVerify::CreateChatroomVerify(const std::string& new_room_id) {
  Debug().info("constructed CreateChatroomVerify");

  this->set("command", command);
  this->set("new_room_id", new_room_id);
}

JoinChatroomCommand::JoinChatroomCommand(const std::string& room_id, const std::string& master_token, const std::string& utoken)
{
  this->set("command", command);
  this->set("room_id", room_id);
  this->set("master_token", master_token);
  this->set("utoken", utoken);
}

ChatroomJoinedCustomer::ChatroomJoinedCustomer(const std::string& cust_id, const std::string& owner_id, const std::string& room_id)
{
  this->set("command", command);
  this->set("cust_id", cust_id);
  this->set("owner_id", owner_id);
  this->set("room_id", room_id);
}


SafeMessageModel::SafeMessageModel(const std::string& crpt_hex, int crpt_len) {
  Debug().info("constructed SafeMessageModel");

  this->set("safe", crpt_hex);
  this->set("safe_len", crpt_len);
}

std::string SafeMessageModel::makeSafeMessage(const std::string& crpt_hex,
                                              int crpt_len) {
  return SafeMessageModel(crpt_hex, crpt_len).to_str();
}