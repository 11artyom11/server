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
                CustomerModel_ptr;

    class ChatRoom
    {
        public:
            ChatRoom(const CustomerModel& master);
            
            int add_new_secondary_customer(const CustomerModel& secondary_customer);
            int remove_secondary_customer (const string& unique_token);
            CustomerModel * const get_customer_by_utoken (const string& unique_token) const noexcept;
            CustomerModel * const get_master (void) const noexcept;

            std::string get_room_id (void) const noexcept;

            int broadcast_to_all_users (const std::string& utoken, const DataTransfer::MessageModel& message) const;

            void dump_state (void) const noexcept;
            ~ChatRoom();

        private:
            /* master customer who owns chatroom */
            CustomerModel_ptr master_customer;

            /* slave customers who are obeyed by owner of chatroom */
            list <CustomerModel_ptr> secondary_customers;

            /* Chat id matches sfd of owner (must be tought over) */
            std::string room_id;

    };
}

#endif /* __CHATROOM_H_ */