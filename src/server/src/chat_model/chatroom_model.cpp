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
        dump_state();
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
    auto token_matcher = [&unique_token] (const CustomerModel_ptr& customer) -> bool {
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
    auto token_matcher = [&unique_token] (const CustomerModel_ptr& customer) {
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

/**
 * @brief Return room_id of *this
 * 
 * @return std::string 
 */
std::string ChatRoom::get_room_id (void) const noexcept
{
    return this->room_id;
}

/**
 * @brief Send recieved from participant of chatroom message to other customers 
 * joined this chatroom 
 * 
 * @param utoken trigger customer utoken
 * @param message json recieved from trigger customer
 * @return count of customers to whom this message has been sent
 */
int ChatRoom::broadcast_to_all_users (const std::string& utoken, const DataTransfer::MessageModel& message) const
{
    Debug().info ("in broadcast_to_all_users");
    int idx = 0;
    auto all_customers = secondary_customers;
    all_customers.push_front (master_customer);

    std::string only_message = message.get<std::string>("message");
    std::string nickname = message.get<std::string>("name");
    DataTransfer::BroadcastMessage brdcstMessage{only_message, utoken, room_id, nickname};

    
    for (const auto& customer : all_customers)
    {
        if (customer->get_unique_token() != utoken)
        {
            customer->send_message(brdcstMessage);
        }
    }
    Debug().info ("out broadcast_to_all_users");
    return idx;
}

/**
 * @brief Print current state of chatroom e.g RoomID MasterUtoken etc
 * 
 */
void ChatRoom::dump_state (void) const noexcept
{
    Debug().raw ("+=========+===================+");
    Debug().raw ("|   Room ID    | ", room_id, " |");
    Debug().raw ("+==============+==============+");
    Debug().raw ("|   Master     | ", master_customer->get_unique_token(), " |");
    Debug().raw ("+==============+==============+");
    int idx = 0;
    for (const auto& sec_customer : secondary_customers)
    {
        Debug().raw ("| Customer ", idx++, " | ", sec_customer->get_unique_token(), " |");
        Debug().raw ("+--------------+--------------+");
    }
    Debug().raw ("| Whole Customer Count : ", idx+1, " |");
    Debug().raw ("+--------------+--------------+");
}

/**
 * 
 * @brief Destroy the Chat Room:: Chat Room object
 * 
 */
ChatRoom::~ChatRoom()
{

}