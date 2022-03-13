#ifndef __MESSAGE_MODEL_H__
#define __MESSAGE_MODEL_H__

#include "../../../../../outter_modules/json/single_include/nlohmann/json.hpp"
#include "../../../helpers/debug_helper/debug_helper.h"
#include <string>


using json = nlohmann::json;
using string = std::string;

namespace DataTransfer
{
    class MessageModel
    {
        public:

             MessageModel();
             explicit MessageModel(const string& json_s) __THROW;
            
             MessageModel (MessageModel&& other_) = delete;

            
            ~MessageModel() = default;

            template <typename ValType>
            void get_into (const string& key, 
                                ValType& into);

            template <typename ValType>
            ValType get (const string& key);

            template <typename ValType>
            void   set (const string& key, 
                            const ValType& value);

            json* const get_json_instance (void) const noexcept;
        private:
        
            json m_message;            
    };





template <typename ValType>
ValType MessageModel::get (const string& key)
{
    return this->m_message.at(key).get<ValType>();
}
            

/**
 * @brief get value from json object of message
 * 
 * @tparam ValType 
 * @param key 
 * @return ValType 
 */
template <typename ValType>
void MessageModel::get_into (const string& key,
                            ValType& into)
{
    into = m_message[key].get<ValType>();
}

/**
 * @brief set value for the certain key for json object of message
 * 
 * @tparam ValType 
 * @param key 
 * @param value 
 */
template <typename ValType>
void MessageModel::set (const string& key,
                            const ValType& value)
{
    // Debug().info("In void MessageModel::set ");
    this->m_message[key] = value;   
    // Debug().info("Out void MessageModel::set ");
}

};
#endif //__MESSAGE_MODEL_H__
