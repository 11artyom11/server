/**
 * @file handler.h
 * @author Artyom Grigorian (grigorianartyom1@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-25
 * @section DESCRIPTION
 * This class is made to handle all incoming and outgoing
 * messages and to keep them in generic way
 * @note Handlers on server and client sides are very simlar, 
 * though still it's not possible to write this class once
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __HANDLER_H__
#define __HANDLER_H__

#include "../../../lib/include/util/data_transfer/message_model/message_model.h"
#include "../../../lib/include/util/data_transfer/message_model/message_templates.h"
#include "../../../lib/include/util/data_transfer/message_resolver/message_resolver.h"
#include "../../../lib/include/util/cyptolib/crypto_unit.h"
#include "../../../lib/include/helpers/constants.h"
#include "../../../lib/include/helpers/debug_helper/debug_helper.h"

#include <map>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

// Helper functor to ease cleanup of container
struct delete_ptr { 
    template <typename P>
    void operator () (P p) {
        delete p;
    }
};

/**
 * @brief class to define string comparison in vector
 * 
 */
class strless {
   public:
      bool operator() (const std::string & first, const std::string & second ) const  { 
         return first < second; 
      }
};

struct ClientPrototype
{
    std::string AES_token;
    std::string unique_token;
};

namespace Client
{
    class Handler;

    /*Binding which help to add new handler functions genreically*/
    typedef std::map <std::string, int (Handler::*) (int, const DataTransfer::MessageModel&), ::strless> CommMapType;

class Handler
{
    public:
        void commap_init (void);

        int send_login_request         (int sfd, const DataTransfer::MessageModel&);
        int send_connect_request       (int sfd, const DataTransfer::MessageModel&);
        int on_connect_accept_recieved (int sfd, const DataTransfer::MessageModel&);
        int on_login_accept_recieved   (int sfd, const DataTransfer::MessageModel&);    
        int send_connect_command       (int sfd, const DataTransfer::MessageModel&);
        int send_login_command         (int sfd, const DataTransfer::MessageModel&);
        int send_sign_up_command       (int sfd, const DataTransfer::MessageModel&);    
        int on_connect_verify_recieved (int sfd, const DataTransfer::MessageModel&);
        int on_sign_up_verify_recieved (int sfd, const DataTransfer::MessageModel&);
        int on_login_verify_recieved   (int sfd, const DataTransfer::MessageModel&);
        int send_terminate_connection  (int sfd, const DataTransfer::MessageModel&);

        decltype(&Client::Handler::send_connect_request) get_command  ( std::string command);

    private:
        CommMapType commap;
        /*Conciously didn't added getter for aes token*/
        ClientPrototype cP;

};

}
#endif /*__HANDLER_H__*/