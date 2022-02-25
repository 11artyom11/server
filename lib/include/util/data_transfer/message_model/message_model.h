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
             MessageModel(const string& json_s) __THROW;
            
            template <typename T>
             MessageModel (T&& other_) __THROW;

            ~MessageModel() = default;

            template <typename ValType>
            void get_into (const string& key, 
                                ValType& into);

            template <typename ValType>
            ValType get (const string& key);

            template <typename ValType>
            void   set (const string& key, 
                            const ValType& value);

        
            json m_message;            
    };



/**
 * @brief Construct a new Message Model:: Message Model object
 * 
 * @param other_rv 
 */
template <typename T>
MessageModel::MessageModel(T&& other_)__THROW :
  m_message{std::forward<T>(other_)}
{
    Debug().info("Constructed new MessageModel object");
}


template <typename ValType>
ValType MessageModel::get (const string& key)
{
    return this->m_message[key];
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
    into = m_message[key];
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
    this->m_message[key] = value;   
}

};
#endif //__MESSAGE_MODEL_H__
