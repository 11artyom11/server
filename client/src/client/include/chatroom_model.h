#ifndef __CLIENT_CHATROOM_H__
#define __CLIENT_HATROOM_H__
#include <list>
#include <string>
#include <unordered_map>
#include <memory>

#include "message_model.h"


using std::list;
using std::string;

class ClientPrototype;

using ClientPrototype_ptr = std::shared_ptr<ClientPrototype>;



class ChatRoom 
{
 public:
  ChatRoom(const ClientPrototype& master);

  ClientPrototype* const get_master(void) const noexcept;

  std::string get_room_id(void) const noexcept;

  int broadcast_to_all_users(const std::string& utoken,
                             const DataTransfer::MessageModel& message) const;

  void dump_state(void) const noexcept;
  ~ChatRoom();

 private:
  /* master Client who owns chatroom */
  const ClientPrototype_ptr master_client;

  /* slave Clients who are obeyed by owner of chatroom */
  list<ClientPrototype_ptr> secondary_clients;

  /* Chat id matches sfd of owner (must be tought over) */
  std::string room_id;
};



/**
 * This class serves as cache type to store chatroom metadata
*/
class ClientPrototype
{
  private:
  /*This container stores pointers to Chatrooms where this client is referred to as master*/
	std::unordered_map<std::string, ChatRoom*>  as_master_chatrooms;
  /*This container stores pointers to Chatrooms where this client is referred to as ordinary customer*/
	std::unordered_map<std::string, ChatRoom*>  as_customer_chatrooms;
  /*This container stores all Chatrooms where this client exists*/
  /*NOTE: Every intance here must be pointed by either customer or master map containers in this cache class*/
	std::list <ChatRoom> chatrooms;
  /*This stores unique token of session in future will be not session but permanent unique token*/
	std::string unique_token; 

  public:

      // ClientPrototype(const std::string& unique_token) noexcept;
      std::string get_unique_token(void) const;
      void set_unique_token(const std::string& unique_token);
      ChatRoom* get_master_room(const std::string& unique_token) const;
      ChatRoom* get_customer_room(const std::string& unique_token) const;
      void register_customer_chatroom(const std::string& unique_token, const ChatRoom& new_room);
      void register_master_chatroom(const std::string& unique_token, const ChatRoom& new_room);
};
#endif /* __CLIENT_CHATROOM_H_ */