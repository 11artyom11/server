/**
 * @file constants.h
 * @author Artyom Grigorian (grigorianartyom1@gmail.com)
 * @brief 
 * @version 0.2
 * @date 2022-03-21
 * 
 * @section DESCRIPTION
 * This file includes all essential and widely used values all over 
 * this project
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __CONSTS__
#define __CONSTS__

#include <vector>
#include <string>
#include <map>

constexpr auto RSA_DEFAULT_PASSPHRASE = "123";

constexpr auto SERVER_NAME = "=> [SERVER] ";
constexpr auto CLIENT_NAME = "=> [CLIENT] ";

constexpr auto ERROR_S      = "[ ERROR ]"; 
constexpr auto INFO_S       = "[ INFO ]";
constexpr auto WARNING_S    = "[ WARNING ]";

constexpr auto DEFAULT_PORT = 9880;
constexpr auto BUFFER_SIZE  = 1024; 
constexpr auto SERVER_IP    = "127.0.0.1";
constexpr auto EXIT_SYM     = '#';

constexpr auto MAX_WRITE_THREAD_COUNT   = 10;
constexpr auto MAX_READ_THREAD_COUNT    = 10;

/*Connect Commands*/
/*
Initial Hansdshake commands which takes p[lace at the beginning of the every
session
*/
constexpr auto CONNECT_REQUEST  = "req_connect";
constexpr auto CONNECT_ACCEPT   = "connect_accept";
constexpr auto CONNECT_COMMAND  = "com_connect";
constexpr auto CONNECT_VERIFY   = "connect_verify";

/*Client Requestes*/
constexpr auto LOG_IN_REQUEST   = "req_log_in";

/* Two sided Commands */
constexpr auto SIGN_UP_COMMAND  = "com_sign_up";
constexpr auto LOG_IN_COMMAND   = "com_log_in";

/* Server Responses */
constexpr auto SIGN_UP_VERIFY   = "sign_up_verify";
constexpr auto LOG_IN_ACCEPT    = "log_in_accept";
constexpr auto LOG_IN_VERIFY    = "log_in_verify";

/*
Kind of this communication during handshake will ne taken 
place

|Server|     sign_up_req            |Client|
|      |   <--------------------    |      |
|      |     sign_up_accept         |      |
|      |   -------------------->    |      |
|      |     com_sign_up            |      |
|      |   <--------------------    |      |
|      |     sign_up_verify         |      |
|      |   -------------------->    |      |
*/




constexpr auto WRITE_COMMAND    = "com_write";
constexpr auto READ_COMMAND     = "com_read";
constexpr auto EXIT_COMMAND     = "com_exit";



constexpr auto TERMINATE_CODE_SUCCESS       = 0x000010;
constexpr auto TERMINATE_CODE_FAILURE       = 0x000011;
constexpr auto UNKNOWN_COMMAND_ERROR        = 0x000012;
constexpr auto INVALID_INITIAL_MESSAGE_DATA = 0x000013; 
constexpr auto UNKNOWN_TEMPLATE_MESSAGE_COMMAND = 0x000014;



const std::vector <std::string> COMMAND_LIST {   
                                                LOG_IN_REQUEST,
                                                CONNECT_REQUEST,

                                                LOG_IN_ACCEPT,
                                                CONNECT_ACCEPT,

                                                CONNECT_COMMAND, 
                                                SIGN_UP_COMMAND, 
                                                LOG_IN_COMMAND,
                                                WRITE_COMMAND,
                                                READ_COMMAND,
                                                EXIT_COMMAND, 
                                                                                    
                                                SIGN_UP_VERIFY,
                                                LOG_IN_VERIFY,
                                                CONNECT_VERIFY,                                               
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
