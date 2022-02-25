#include "../../../../include/util/data_transfer/message_model/message_model.h"

using json = nlohmann::json;
using string = std::string;
using namespace DataTransfer;

MessageModel::MessageModel()
{

}

/**
 * @brief Construct a new Message Model:: Message Model object
 * 
 * @param json_s 
 */
MessageModel::MessageModel (const string& json_s) __THROW :
    m_message(json_s)
{
    Debug().info("Constructed new MessageModel object");
}
