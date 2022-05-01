#include "chatroom_manager.h"



/**
 * @brief Returns array of chatroom pointers 
 * which belong to customer passed as parameter
 * 
 * @note Can be used to add or remove chatroom from 
 * array (vector) bc function returns reference
 * to array (direct access to chatroom array is guaranteed)
 * 
 * @param master master customer pointer
 * @return vector <Server::ChatRoom_shrd_ptr>& array of owning chatrooms
 */
vector <Server::ChatRoom_shrd_ptr>& 
Server::ChatRoomManager::operator [] (Customer::CustomerModel * master) 
{
    std::string utoken = master->get_unique_token();
    return this->operator[] (utoken);
}

/**
 * @brief Returns array of chatroom pointers 
 * which belong to customer unique token passed as parameter
 * 
 * @note Can be used to add or remove chatroom from 
 * array (vector) bc function returns reference
 * to array (direct access to chatroom array is guaranteed)
 * 
 * @param utoken master customer unique token
 * @return vector <Server::ChatRoom_shrd_ptr>& array of owning chatrooms
 */
vector <Server::ChatRoom_shrd_ptr>&
Server::ChatRoomManager::operator [] (const std::string& utoken)
{
    return chatroom_lst[utoken];
}

/**
 * @brief 
 * 
 * @return vector <ChatRoom_shrd_ptr>& 
 */
vector <Server::ChatRoom_shrd_ptr>& 
Server::ChatRoomManager::push_new_room (Customer::CustomerModel* master, 
                                            RoomSpace::ChatRoom* new_room)
{
    this->operator[] (master).emplace_back (std::make_shared<RoomSpace::ChatRoom>(*new_room));
    Debug().info ("Customer token => ", master->get_unique_token());
    Debug().info ("Added room id => ", new_room->get_room_id());
    Debug().info ("Updated rooms count : ",this->operator[] (master).size());

    return chatroom_lst[master->get_unique_token()];
}

/**
 * @brief Delete chat from according chat array which matches by id to passed argument
 * 
 * @param master customer to know from where del
 * @param chat_id 
 * @return vector <Server::ChatRoom_shrd_ptr>& 
 */
vector <Server::ChatRoom_shrd_ptr>&
Server::ChatRoomManager::remove_room_from (Customer::CustomerModel* master,
                                                const std::string& room_id)
{
    //erase(std::remove(vec.begin(), vec.end(), 8), vec.end());
    auto master_room_arr = this->operator[] (master);

    /*Deletes from according chatroom array chatroom pointer which matches by chat_id to passed one*/
    master_room_arr.erase(std::remove_if (master_room_arr.begin(), 
                                            master_room_arr.end(), 
                                            [&room_id](const ChatRoom_shrd_ptr& chatroom_ptr)
                                            {
                                                return !(chatroom_ptr->get_room_id().compare(room_id));
                                            }), master_room_arr.end());

    return master_room_arr;

}

/**
 * @brief Deletes all the rooms owned by customer 
 * passed as argument
 * 
 * @return vector <Server::ChatRoom_shrd_ptr>& 
 */
Server::ChatRoom_Map_Type&
Server::ChatRoomManager::remove_all_rooms (Customer::CustomerModel* master)
{
    this->chatroom_lst.erase(master->get_unique_token());
    Debug().info ("deleted all rooms related to customer => ", master->get_unique_token());
    return chatroom_lst;
}


/**
 * @brief Returns shared pointer of certain room
 * 
 * @param master_token 
 * @param room_id 
 * @return Server::ChatRoom_shrd_ptr 
 */
Server::ChatRoom_shrd_ptr 
Server::ChatRoomManager::get_room_by_id ( std::string master_token,
                                             std::string room_id) 
{
    auto rooms = this->operator[](master_token);
    auto room_it = find_if (rooms.begin(), 
                            rooms.end(), 
                            [&room_id](const ChatRoom_shrd_ptr& room_ptr)
                            {
                                return !(room_ptr->get_room_id().compare(room_id));                            
                            });
    if (room_it != rooms.end()) return *room_it;
    else throw -1;
}

