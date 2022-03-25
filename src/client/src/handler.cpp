#include "../include/handler.h"

using Handler = Client::Handler;

void commap_init (void)
{

}

int Handler::send_login_request(int sfd,
                                     const DataTransfer::MessageModel&)
{
    commap[CONNECT_REQUEST]   = &Handler::send_connect_request;
    commap[LOG_IN_REQUEST]    = &Handler::send_login_request;
    commap[CONNECT_ACCEPT]    = &Handler::on_connect_accept_recieved;
    commap[LOG_IN_ACCEPT]     = &Handler::on_login_accept_recieved;
    commap[CONNECT_COMMAND]   = &Handler::send_connect_command;
    commap[LOG_IN_COMMAND]    = &Handler::send_login_command;
    commap[SIGN_UP_COMMAND]   = &Handler::send_sign_up_command;
    commap[EXIT_COMMAND]      = &Handler::send_terminate_connection;
    commap[CONNECT_VERIFY]    = &Handler::on_connect_verify_recieved;
    commap[LOG_IN_VERIFY]     = &Handler::on_login_verify_recieved;
    commap[SIGN_UP_VERIFY]    = &Handler::on_sign_up_verify_recieved;
}

int Handler::send_connect_request(int sfd, 
                                    const DataTransfer::MessageModel&)
{

}

int Handler::on_connect_accept_recieved(int sfd,
                                            const DataTransfer::MessageModel&)
{
    Debug().warning ("on_connect_accept_recieved");
}   

int Handler::on_login_accept_recieved(int sfd,
                                        const DataTransfer::MessageModel&)
{

}

int Handler::send_connect_command(int sfd,
                                    const DataTransfer::MessageModel&)
{

}

int Handler::send_login_command(int sfd,
                                     const DataTransfer::MessageModel&)
{

}

int Handler::send_sign_up_command(int sfd, 
                                    const DataTransfer::MessageModel&)
{

}

int Handler::on_connect_verify_recieved(int sfd,
                                            const DataTransfer::MessageModel&)
{

}

int Handler::on_sign_up_verify_recieved(int sfd, 
                                            const DataTransfer::MessageModel&)
{

}

int Handler::on_login_verify_recieved(int sfd,
                                        const DataTransfer::MessageModel&)
{

}

int Handler::send_terminate_connection(int sfd,
                                        const DataTransfer::MessageModel&)
{

}

decltype(&Client::Handler::send_connect_request) 
Handler::get_command  ( std::string command)
{
    try
    {
        Debug().info("SIZE : ", commap.size());
        return commap.at(command);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return nullptr;
    }
}

