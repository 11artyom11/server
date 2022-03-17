#ifndef __CONSTS__
#define __CONSTS__

#include <vector>
#include <string>
#include <map>

constexpr auto RSA_DEFAULT_PASSPHRASE = "123";

constexpr auto SERVER_NAME = "=> [SERVER] ";
constexpr auto CLIENT_NAME = "=> [CLIENT] ";

constexpr auto ERROR_S      = "[ERROR] : "; 
constexpr auto INFO_S       = "[INFO] : ";
constexpr auto WARNING_S    = "[WARNING] : ";

constexpr auto DEFAULT_PORT = 9880;
constexpr auto BUFFER_SIZE  = 1024; 
constexpr auto SERVER_IP    = "127.0.0.1";
constexpr auto EXIT_SYM     = '#';

constexpr auto MAX_WRITE_THREAD_COUNT   = 10;
constexpr auto MAX_READ_THREAD_COUNT    = 10;

constexpr auto SIGN_NEW_CUSTOMER_MESSAGE = "0";
constexpr auto WRITE_REQ                 = "1";
constexpr auto READ_REQ                  = "2";
constexpr auto EXIT_MESSAGE              = "3";

constexpr auto TERMINATE_CODE_SUCCESS       = 0x000010;
constexpr auto TERMINATE_CODE_FAILURE       = 0x000011;
constexpr auto UNKNOWN_COMMAND_ERROR        = 0x000012;
constexpr auto INVALID_INITIAL_MESSAGE_DATA = 0x000013; 
constexpr auto UNKNOWN_TEMPLATE_MESSAGE_COMMAND = 0x000014;

constexpr auto SIGN_UP_COMMAND = "sign_up";
constexpr auto LOG_IN_COMMAND  = "log_in";

const std::vector <std::string> COMMAND_LIST {SIGN_UP_COMMAND, 
                                                LOG_IN_COMMAND
                                                /*etc....*/};


const std::vector <std::string> SIGN_UP_DATA_KEYS{"command"};
const std::vector <std::string> LOG_IN_DATA_KEYS {"log_in"};

const std::map    <std::string, std::vector <std::string>>
COMMAND_DATA_KEY_BINDINGS
{
    {SIGN_UP_COMMAND, {SIGN_UP_DATA_KEYS}},
    {LOG_IN_COMMAND,  {LOG_IN_DATA_KEYS}}
};

#endif //__CONSTS
