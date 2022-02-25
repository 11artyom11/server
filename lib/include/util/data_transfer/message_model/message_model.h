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

             explicit MessageModel(const string& json_s) __THROW;
            template <typename T>
             MessageModel (T&& other_) __THROW;

            ~MessageModel() = default;

        private:
            json m_message;            
    };
};

#endif //__MESSAGE_MODEL_H__
