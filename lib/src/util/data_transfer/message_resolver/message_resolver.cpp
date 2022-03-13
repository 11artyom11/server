#include "../../../../include/util/data_transfer/message_resolver/message_resolver.h"

using MessageResolver  = DataTransfer::MessageResolver ;
using MessageModel     = DataTransfer::MessageModel;

/**
 * @brief Construct a new Message Resolver:: Message Resolver object
 * 
 */
MessageResolver::MessageResolver()
{

}

/**
 * @brief recieve a command which will tell what kind of message template 
 * creator will be created
 * 
 * @param init_data init data std::map which is filled by key-value
 * needed for message constructing
 * @param command enum type 
 * @return MessageModel instance which is filled by passed data
 */
MessageModel MessageResolver::distribute_command(const std::map<string, JsonValType>& init_data,
                                                    DataTransfer::COMMAND_NAME command) const
{
    /*If passed initial data is ill formed throw corresponding exception*/
    if (!is_message_initial_data_valid(command, init_data))
    {
        throw INVALID_INITIAL_MESSAGE_DATA;
    }

    switch (command)
    {
    case DataTransfer::COMMAND_NAME::SIGN_UP:
        return init_sign_up_message(init_data);    

    case DataTransfer::COMMAND_NAME::LOG_IN:
        return init_log_in_message(init_data);

    default:
        throw UNKNOWN_TEMPLATE_MESSAGE_COMMAND;
    }

}

/**
 * @brief create message model by passed map data
 * 
 * 
 * @param init_data multi-typed map containing all needed data
 * for **LOGIN** message constructing
 * @return MessageModel 
 */
MessageModel MessageResolver::init_log_in_message (const std::map<string, JsonValType>& init_data) const __THROW
{
    MessageModel mes;
    
}

/**
 * @brief create message model by passed map data
 * 
 * 
 * @param init_data multi-typed map containing all needed data
 * for **SIGNUP** message constructing
 * @return MessageModel 
 */
MessageModel MessageResolver::init_sign_up_message(const std::map<string, JsonValType>& init_data) const __THROW
{

}


/**
 * @brief check if all needed for certain message template data 
 * exists in associative container
 * 
 * Data is passing in this form
 * +-----------------------+
 * | "command" | "sign_up" |
 * | "username"| "username"|
 * | "passwd"  | "********"|
 * +-----------------------+
 * 
 * @return true if all OK
 * @return false if at least one of ESSENTIAL data doesnt exist
 */
bool DataTransfer::is_message_initial_data_valid( DataTransfer::COMMAND_NAME cN,
                                        const std::map <string, JsonValType> & data)
{
    switch (cN)
    {
        case DataTransfer::COMMAND_NAME::SIGN_UP :
        {
            for ( auto c_key : SIGN_UP_KEY_COMMANDS)
            {
                try
                {
                    (void)data.at(c_key);
                }
                catch(const std::exception& e)
                {
                    Debug().fatal("CAUGHT ERROR : ", INVALID_INITIAL_MESSAGE_DATA);
                    return false;
                }
            }
            return true;
        }
        case DataTransfer::COMMAND_NAME::LOG_IN :
        {
            for ( auto c_key : LOG_IN_KEY_COMMANDS)
            {
                try
                {
                    (void)data.at(c_key);
                }
                catch(const std::exception& e)
                {
                    Debug().fatal("CAUGHT ERROR : ", INVALID_INITIAL_MESSAGE_DATA);
                    return false;
                }
            }
            return true;    
        }

        default:
            return false;

    }
}


/**
 * @brief check if all needed for certain message template data 
 * exists in MessageModel instance
 * 
 * @return true if all OK
 * @return false if at least one of ESSENTIAL data doesnt exist
 */
bool DataTransfer::is_message_initial_data_valid ( MessageModel& mModel)
{
    DataTransfer::COMMAND_NAME command;
    try
    {
        command = get_command_from_s(mModel.get<std::string>("command"));
    }
    catch(const std::exception& e)
    {
        throw INVALID_INITIAL_MESSAGE_DATA;
    }
    auto map = static_cast<nlohmann::json*>(mModel.get_json_instance())->get<std::map<string, JsonValType>>();

    
}

DataTransfer::COMMAND_NAME DataTransfer::get_command_from_s (std::string command) 
{
    if (command == SIGN_UP_COMMAND)
    {
        return DataTransfer::COMMAND_NAME::SIGN_UP;
    }
    if (command == LOG_IN_COMMAND)
    {
        return DataTransfer::COMMAND_NAME::LOG_IN;
    }
}

DataTransfer::MessageResolver::~MessageResolver()
{

}
