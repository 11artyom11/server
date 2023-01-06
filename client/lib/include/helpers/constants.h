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

#include <map>
#include <string>
#include <vector>

constexpr auto SIL_SUCCESS = 0;

constexpr auto RSA_DEFAULT_PASSPHRASE = "123";

constexpr auto SERVER_NAME = "=> [SERVER] ";
constexpr auto CLIENT_NAME = "=> [CLIENT] ";

constexpr auto ERROR_S = "[ ERROR ]";
constexpr auto INFO_S = "[ INFO ]";
constexpr auto WARNING_S = "[ WARNING ]";

constexpr auto DEFAULT_PORT = 9880;
constexpr auto BUFFER_SIZE = 1024;
constexpr auto AES_KEY_LEN = 16; /* BYTES <<AES128 is used by default>>*/
constexpr auto SERVER_IP = "127.0.0.1";
constexpr auto EXIT_SYM = '#';

constexpr auto MAX_WRITE_THREAD_COUNT = 10;
constexpr auto MAX_READ_THREAD_COUNT = 10;
constexpr auto MAX_JSON_MESSAGE_SIZE = 1024;

/*Connect Commands*/
/*
Initial Hansdshake commands which takes p[lace at the beginning of the every
session
*/
constexpr auto CONNECT_REQUEST = "req_connect";
constexpr auto CONNECT_ACCEPT = "connect_accept";
constexpr auto CONNECT_COMMAND = "com_connect";
constexpr auto CONNECT_VERIFY = "connect_verify";

/*Client Requestes*/
constexpr auto LOG_IN_REQUEST = "req_log_in";

/* Two sided Commands */
constexpr auto SIGN_UP_COMMAND = "com_sign_up";
constexpr auto LOG_IN_COMMAND = "com_log_in";
constexpr auto CREATE_CHATROOM_COMMAND = "com_crt_chatroom";
constexpr auto JOIN_CHATROOM_COMMAND = "com_join_chatroom";
constexpr auto BRDCST_MESSAGE_COMMAND = "com_brdcst_message";

/* Server Responses */
constexpr auto SIGN_UP_VERIFY = "sign_up_verify";
constexpr auto LOG_IN_ACCEPT = "log_in_accept";
constexpr auto LOG_IN_VERIFY = "log_in_verify";
constexpr auto CHATROOM_CREATE_VERIFY = "chatroom_crt_verify";
constexpr auto CHATROOM_JOINED_CUSTOMER = "chatroom_joined_customer";

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

constexpr auto WRITE_COMMAND = "com_write";
constexpr auto READ_COMMAND = "com_read";
constexpr auto EXIT_COMMAND = "com_exit";

constexpr auto TERMINATE_CODE_SUCCESS = 0x000010;
constexpr auto TERMINATE_CODE_FAILURE = 0x000011;
constexpr auto UNKNOWN_COMMAND_ERROR = 0x000012;
constexpr auto INVALID_INITIAL_MESSAGE_DATA = 0x000013;
constexpr auto UNKNOWN_TEMPLATE_MESSAGE_COMMAND = 0x000014;

const std::vector<std::string> COMMAND_LIST{
    LOG_IN_REQUEST,          CONNECT_REQUEST,

    LOG_IN_ACCEPT,           CONNECT_ACCEPT,

    CONNECT_COMMAND,         SIGN_UP_COMMAND,       LOG_IN_COMMAND,
    CREATE_CHATROOM_COMMAND, JOIN_CHATROOM_COMMAND, BRDCST_MESSAGE_COMMAND,
    WRITE_COMMAND,           READ_COMMAND,          EXIT_COMMAND,

    SIGN_UP_VERIFY,          LOG_IN_VERIFY,         CONNECT_VERIFY,
    /*etc....*/};

const std::vector<std::string> SIGN_UP_DATA_KEYS{"command"};
const std::vector<std::string> LOG_IN_DATA_KEYS{"log_in"};

const std::map<std::string, std::vector<std::string>> COMMAND_DATA_KEY_BINDINGS{
    {SIGN_UP_COMMAND, {SIGN_UP_DATA_KEYS}},
    {LOG_IN_COMMAND, {LOG_IN_DATA_KEYS}}};


static const char GREETING_MESSAGE[] = {\
"******************************************************************\n" \
"*       _________.___.____ ____   _________________________      *\n"\
"*      /   _____/|   |    |\\   \\ /   /\\_   _____/\\______   \\     *\n"\
"*      \\_____  \\ |   |    | \\   Y   /  |    __)_  |       _/     *\n"\
"*      /        \\|   |    |__\\     /   |        \\ |    |   \\     *\n"\
"*     /_______  /|___|_______ \\___/   /_______  / |____|_  /     *\n"\
"*             \\/             \\/               \\/         \\/      *\n"\
    "* 1 - Config connection                                          *\n"\
    "* 2 - Create Chatroom                                            *\n"\
    "* 3 - Get Chatroom info                                          *\n"\
    "* 4 - Join Chatroom                                              *\n"\
    "******************************************************************\n"\
  };

constexpr auto CONFIG_CONNECTION = "1";
constexpr auto CREATE_CHATROOM = "2";
constexpr auto GET_CHATROOM_INFO = "3";
constexpr auto JOIN_CHATROOM = "4";

#endif  //__CONSTS
