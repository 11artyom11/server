#ifndef __CHATROOM_H__
#define __CHATROOM_H__
#include "customer.h"
#include <list>


using namespace Customer;
using std::list;
using std::string;

namespace RoomSpace
{
    typedef std::shared_ptr <CustomerModel> \
                CustomerModel_shrd_ptr;

    class ChatRoom
    {
        public:
            ChatRoom(const CustomerModel& master);
            
            int add_new_secondary_customer(const CustomerModel& secondary_customer);
            int remove_secondary_customer (const string& unique_token);
            CustomerModel * const get_customer_by_utoken (const string& unique_token) const noexcept;
            CustomerModel * const get_master (void) const noexcept;

            ~ChatRoom();

        private:
            CustomerModel_shrd_ptr master_customer;
            list <CustomerModel_shrd_ptr> secondary_customers;
            uint64_t chat_id;

    };
}

#endif /* __CHATROOM_H_ */