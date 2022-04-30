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
                                                const std::string& chat_id)
{
    //erase(std::remove(vec.begin(), vec.end(), 8), vec.end());
    auto master_room_arr = this->operator[] (master);

    /*Deletes from according chatroom array chatroom pointer which matches by chat_id to passed one*/
    master_room_arr.erase(std::remove_if (master_room_arr.begin(), 
                                            master_room_arr.end(), 
                                            [&chat_id](const ChatRoom_shrd_ptr& chatroom_ptr)
                                            {
                                                return !(chatroom_ptr->get_chat_id().compare(chat_id));
                                            }), master_room_arr.end());

    return master_room_arr;

}
