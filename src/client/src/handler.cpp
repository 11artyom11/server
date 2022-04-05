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

    RSA_Unit rsaU;
    AES_Unit aesU;
    string key = message.get<std::string>("pkey");
    unsigned char* mes = (unsigned char*)"{\"command\":\"com_connect\"}\0";
    unsigned char* enc = rsaU.rsa_encrypt(mes,(char*)key.c_str());
    for (size_t i = 0; i < 128; i++) 
    {
        fprintf(stderr, "0x%02x/", enc[i]);
    }
    fprintf(stderr, "\n");

    char* b64 = base64encode(enc, strlen ((const char*)enc));
    char* d64 = base64decode(b64, strlen(b64));
    Debug().fatal("---------");
    for (size_t i = 0; i < 128; i++) 
    {
        fprintf(stderr, "0x%02x/", d64[i]);
    }
    fprintf(stderr, "\n");

    send(sfd, b64, strlen(b64), NULL );
    // delete[] mes;
    delete[] b64;
    delete[] enc;
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

    string key = message.get<string>("pkey").c_str();
    Debug().warning(key);

    cP.AES_token = base64encode((char*)aesU.generate_key(256), 256);
    // cP.unique_token = message.get<string> ("unique_token");

    DataTransfer::ConnectCommand cC ("192.168.1.1",cP.AES_token, cP.unique_token);

    // unsigned char* mes_raw_str = (unsigned char*)(cC.to_str().c_str());
    /*@note make tmp function call*/
    
    Debug().info ((unsigned char*)(cC.to_str().c_str()), "\n!!!!!!!!!");
    unsigned char* mes_enc_str =  rsaU.rsa_encrypt((unsigned char*)(cC.to_str().c_str()), (char*)key.c_str());
    // char* mes_b64_enc_str = base64encode(mes_enc_str, strlen((const char*)mes_enc_str));
    // Debug().warning("To be sent~!!!");
    // Debug().info (mes_b64_enc_str);
    send (sfd, mes_enc_str, 128, NULL);
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

