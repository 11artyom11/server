#ifndef __MESSAGE_RESOLVER_H__
#define __MESSAGE_RESOLVER_H__

#include <string>
#include <map>
#include <algorithm>
#include <any>


#include "../message_model/message_model.h"
#include "../../../../../lib/include/helpers/constants.h"

using  string        = std::string ;
// using  std::map           = std::std::map;
using  JsonValType   = std::any;


namespace DataTransfer
{
    enum class COMMAND_NAME 
    {
        SIGN_UP, 
            LOG_IN
    };

    /**
     * @brief This class is designed to support instant 
     * message template support via helper functions
     * 
     */

    class MessageResolver
    {
        public:
            MessageResolver();
            MessageModel distribute_command(const std::map<string, JsonValType>&,
                                                COMMAND_NAME cN) const;

            MessageModel init_log_in_message 
             (const std::map<string, JsonValType>&) const __THROW;

             MessageModel init_sign_up_message
             (const std::map<string, JsonValType>&) const __THROW;

            ~MessageResolver();
    };

    bool is_message_initial_data_valid (COMMAND_NAME cN, 
                                        const std::map<string, JsonValType> &);

    bool is_message_valid ( MessageModel& mModel);

    COMMAND_NAME get_command_from_s (std::string command) ;
}

#endif //__MESSAGE_RESOLVER_H__