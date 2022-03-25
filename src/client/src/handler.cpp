#include "../include/handler.h"

using Handler = Client::Handler;

void Handler::commap_init (void)
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

int Handler::send_login_request(int sfd,
                                     const DataTransfer::MessageModel&)
{
 
}

int Handler::send_connect_request(int sfd, 
                                    const DataTransfer::MessageModel&)
{

}

int Handler::on_connect_accept_recieved(int sfd,
                                            const DataTransfer::MessageModel& message)
{
    Debug().info ("in on_connect_accept_recieved");
    /*
    Recieve RSA public key from server, cipher by it aes token and send 
    ecncrypted token to server
    */

   
   send_connect_command(sfd, message);
    
    return 0;
}   

int Handler::on_login_accept_recieved(int sfd,
                                        const DataTransfer::MessageModel&)
{

}

int Handler::send_connect_command(int sfd,
                                    const DataTransfer::MessageModel& message)
{
    RSA_Unit rsaU;
    AES_Unit aesU;

    string key = message.get<string>("pkey"); 
    
    cP.AES_token = string_to_hex((char*)aesU.generate_key(256));
    cP.unique_token = message.get<string> ("unique_token");

    DataTransfer::ConnectCommand cC ("192.168.1.1",cP.AES_token, cP.unique_token);

    auto mes_raw_str = cC.to_str().c_str();
    Debug().info (cC.to_str().c_str());

    send (sfd, cC.to_str().c_str(), strlen(cC.to_str().c_str()), NULL);
    return 0;
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
    Debug().info ("CONNECTION VERIFIED");
return 0;
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

