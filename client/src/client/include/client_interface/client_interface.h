#include <iostream>
#include <sstream>
#include <semaphore.h>
#include <unordered_map>
#include <vector>
#include "constants.h"

enum INTERFACE_COMMANDS
{
    GREET_COMMAND  
};



class ClientInterface 
{
    public:
        std::vector<std::string> scan_command ();
        void greet_message(void);
        std::vector<std::string> buffer;
        std::vector<std::string>& config_connection (void);
        std::vector<std::string>& create_chatroom (void);
        std::vector<std::string>& get_chatroom_info (void);
        std::vector<std::string>& join_chatroom (void);
                      
};

std::unordered_map <std::string, 
                        std::vector<std::string>& (ClientInterface::*)(void)> scanMap
{
    {CONFIG_CONNECTION, &ClientInterface::config_connection},
    {CREATE_CHATROOM, &ClientInterface::create_chatroom},
    {GET_CHATROOM_INFO, &ClientInterface::get_chatroom_info},
    {JOIN_CHATROOM, &ClientInterface::join_chatroom}
};