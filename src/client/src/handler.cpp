#include "../include/handler.h"

using Handler = Client::Handler;

Handler::Handler ()
{
    aes_shrd_ptr = std::make_unique<AES_Unit>();
    rsa_shrd_ptr = std::make_unique<RSA_Unit>();

}

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
    this->current_state = CONNECT_STATE::conn_request;
}

int Handler::on_connect_accept_recieved(int sfd,
                                            const DataTransfer::MessageModel& message)
{

    Debug().info ("in on_connect_accept_recieved");
    /*
    Recieve RSA public key from server, cipher by it aes token and send 
    ecncrypted token to server
    */
    this->current_state = CONNECT_STATE::conn_accept;

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
    
    Debug().info ("In send_connect_command");
    auto key = "ABCDEF1234567890"; //aes_shrd_ptr->generate_key(16);
    auto utoken = message.get<string>("unique_token");
    
    cP.AES_token = key;
    cP.unique_token = utoken;

    DataTransfer::ConnectCommand cC{"localhost",std::string{key},utoken};

    // char* response = (char*)(cC.to_str().c_str());
    auto str = cC.to_str();
    const auto str_length = str.length();
    Debug().info ((char*)str.c_str());
    send (sfd, (char*)str.c_str(), str_length, NULL);
    this->current_state = CONNECT_STATE::conn_commnd;
    
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
                                            const DataTransfer::MessageModel& message)
{
    
    string utoken = message.get<string>("unique_token");

    if (utoken == cP.unique_token)
    {
        Debug().info ("CONNECTION VERIFIED");
        this->current_state = CONNECT_STATE::conn_verify;
    }
    else 
    {
        Debug().fatal ("Tokens donot match");
    }


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

RSA_Unit_shrd_ptr
Handler::get_rsa_ptr (void) const
{
    return this->rsa_shrd_ptr;
}

AES_Unit_shrd_ptr
Handler::get_aes_ptr (void) const
{
    return this->aes_shrd_ptr;
}

CONNECT_STATE Handler::get_net_state(void) const
{
    return this->current_state;
}

ClientPrototype const* 
Handler::get_client_prototype_ptr_c (void) const
{
    return &(this->cP);
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

