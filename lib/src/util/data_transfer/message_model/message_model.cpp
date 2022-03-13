#include "../../../../include/util/data_transfer/message_model/message_model.h"

using json = nlohmann::json;
using string = std::string;
using namespace DataTransfer;

MessageModel::MessageModel() :
    MessageModel ("{}")
{

}

/**
 * @brief Construct a new Message Model:: Message Model object
 * 
 * @param json_s 
 */
MessageModel::MessageModel (const string& json_s) __THROW :
    m_message(json::parse(json_s))
{
    Debug().info("Constructed new MessageModel object");
}



/**
 * @brief return pointer const to json object
 * means that pointed object cannot be edited via returned ptr
 * 
 * @return json* const pointer to json object
 */
json* const MessageModel::get_json_instance (void) const noexcept
{
    json* const js_obj_ptr = (json* const)(&this->m_message);
    return js_obj_ptr;
}

