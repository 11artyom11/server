/**
 * @file chatroom_manager.h
 * @author Grigorian Artyom (grigorianartyom1@gmail.com)
 * @brief
 *  This header is implemented to manage chatroom creation process 
 * at a higher (abstract level)
 * @version 0.1
 * @date 2022-04-30
 * 
 * @section Last Changes by Artyom Grigorian 2022-04-30
 * Created Manager class prototype
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __CHATROOM_MANAGER_H__
#define __CHATROOM_MANAGER_H__

#include "chatroom_model.h"
#include "customer.h"
#include "debug_helper.h"

#include <map>
#include <vector>
#include <memory>

using std::unordered_map;
using std::vector;

namespace Server
{

    template <typename T>
    using shared_ptr = std::shared_ptr<T>;

    /*Shared ptr type for Customer Model*/
    typedef shared_ptr<Customer::CustomerModel> \
                            CustomerModel_shrd_ptr;    

    /* Shared ptr type for ChatRoom instances */
    typedef shared_ptr<RoomSpace::ChatRoom>\
                             ChatRoom_shrd_ptr;
    
    typedef unordered_map <std::string, vector<ChatRoom_shrd_ptr>>\
                                ChatRoom_Map_Type;

    class ChatRoomManager
    {
        public:
            ChatRoomManager()   = default;
            ~ChatRoomManager()  = default;

            vector <ChatRoom_shrd_ptr>& operator [] (Customer::CustomerModel *) ;
            vector <ChatRoom_shrd_ptr>& operator [] (const std::string&);

            vector <ChatRoom_shrd_ptr>& push_new_room (Customer::CustomerModel*, RoomSpace::ChatRoom*);
            vector <ChatRoom_shrd_ptr>& remove_room_from (Customer::CustomerModel*,const std::string& chat_id);
            ChatRoom_Map_Type& remove_all_rooms (Customer::CustomerModel*);
            ChatRoom_shrd_ptr get_room_by_id ( std::string master_token, 
                                                     std::string room_id);
        private:
            ChatRoom_Map_Type chatroom_lst;
    };
}

#endif //__CHATROOM_MANAGER_H__