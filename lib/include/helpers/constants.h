#ifndef __CONSTS__
#define __CONSTS__
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

constexpr auto TERMINATE_CODE_SUCCESS = 0x000010;
constexpr auto TERMINATE_CODE_FAILURE = 0x000011;
constexpr auto UNKNOWN_COMMAND_ERROR = 0x000012;

#endif //__CONSTS
