#include "chatroom_model.h"

using namespace RoomSpace;

std::string random_string(int len = 10)
{
    std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

    std::random_device rd;
    std::mt19937 generator(rd());

    std::shuffle(str.begin(), str.end(), generator);

    return str.substr(0, len); // assumes 32 < number of characters in str
}

/**
 * @brief Construct a new Chat Room:: Chat Room object
 * 
 * @param master The master customer who is the owner of chatroom
 */
ChatRoom::ChatRoom(const CustomerModel& master) :
        room_id{random_string(10)}
{
    
    this->master_customer = std::make_shared<CustomerModel> (master);
}

/**
 * @brief Add new secondary Customer 
 * 
 * @param secondary_customer Customer Model instance to be added 
 * @return int 0 on success other value on failure
 */
int ChatRoom::add_new_secondary_customer(const CustomerModel& secondary_customer)
{
    try
    {
        secondary_customers.push_back(std::make_shared<CustomerModel>(secondary_customer));
        Debug().info ("Slave count after Call => ", secondary_customers.size());
        return 0;
    }
    catch (std::exception& e)
    {
        return -1;
    }

}

/**
 * @brief Remove secondary customer from main list by unqiue token
 * 
 * @param unique_token unique token by which customer will be removed
 * @return int 0 on success other value on failure
 */
int ChatRoom::remove_secondary_customer (const string& unique_token)
{
    auto token_matcher = [&unique_token] (const CustomerModel_shrd_ptr& customer) -> bool {
        if (customer.get()->get_unique_token().compare(unique_token) == 0)
        {
            return true;
        } 
        return false;
    };

    try
    {
        secondary_customers.remove_if (token_matcher);
        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }

}

/**
 * @brief Returm secondary customer instance pointer by unique token
 * 
 * @param unique_token 
 * @return CustomerModel* const
 */
CustomerModel * const ChatRoom::get_customer_by_utoken (const string& unique_token) const noexcept
{
    auto token_matcher = [&unique_token] (const CustomerModel_shrd_ptr& customer) {
         if (customer.get()->get_unique_token().compare(unique_token) == 0)
        {
            return true;
        } 
        return false;
    };
    auto customer_it = std::find_if (secondary_customers.begin(),secondary_customers.end(),token_matcher);
    return (*customer_it).get();
}

/**
 * @brief Return pointer on constant instance of master of ChatRoom
 * 
 * @return CustomerModel* const 
 */
CustomerModel * const ChatRoom::get_master (void) const noexcept
{
    return master_customer.get();
}

std::string ChatRoom::get_room_id (void) const noexcept
{
    return this->room_id;
}

/**
 * 
 * @brief Destroy the Chat Room:: Chat Room object
 * 
 */
ChatRoom::~ChatRoom()
{

}