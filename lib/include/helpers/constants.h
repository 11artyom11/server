#ifndef __CONSTS__
#define __CONSTS__

constexpr auto SERVER_NAME = "=> [SERVER] ";
constexpr auto CLIENT_NAME = "=> [CLIENT] ";

constexpr auto ERROR_S      = "[ERROR] : "; 
constexpr auto INFO_S       = "[INFO] : ";
constexpr auto WARNING_S    = "[WARNING] : ";

constexpr auto DEFAULT_PORT = 9888;
constexpr auto BUFFER_SIZE  = 1024; 
constexpr auto SERVER_IP    = "127.0.0.1";
constexpr auto EXIT_SYM     = '#';

constexpr auto MAX_WRITE_THREAD_COUNT   = 10;
constexpr auto MAX_READ_THREAD_COUNT    = 10;

constexpr auto WRITE_REQ    = 0;
constexpr auto READ_REQ     = 1;

#endif //__CONSTS
