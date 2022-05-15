#include <customer.h>

using namespace Customer;

CustomerModel::CustomerModel(int sfd, 
                                const std::string& unique_token,
                                    const aes_shrd_ptr& aes,
                                        const rsa_shrd_ptr& rsa) :
    sfd{sfd},
    unique_token{unique_token}

{
    Debug().info("Retrieved data SFD : ", sfd, " UNIQUE TOKEN : ", unique_token);
    crypto_unit = std::make_unique<Security::CustomerCryptoUnit>(Security::CustomerCryptoUnit(aes, rsa, sfd));
}

int CustomerModel::get_sfd(void) const noexcept
{
    return this->sfd;
}

std::string CustomerModel::get_unique_token (void) const noexcept
{
    return this->unique_token;
}


/**
 * @brief Set aes token for Customer model
 * 
 * @param token 
 */
void CustomerModel::set_aes_token (const std::string& token)
{
    this->crypto_unit->set_aes_token( token);
    return;
}

/**
 * @brief Returns aes token as std::string !!! may be unsafe 
 * Need to be reviewed though is on server side
 * 
 * @return std::string 
 */
std::string CustomerModel::get_aes_token (void) const noexcept
{
    return crypto_unit->get_aes_token();
}

/**
 * @brief Return crpytounit
 * 
 * @return Security::CustomerCryptoUnit* 
 */
Security::CustomerCryptoUnit* CustomerModel::get_crypto_unit(void)
{
    return this->crypto_unit.get();
}


void CustomerModel::send_message (const DataTransfer::MessageModel& message)
{
    std::string aes_key = get_aes_token();
    unsigned char key_c[aes_key.length()];  // = (unsigned char*)(get_aes_token().c_str());
    unsigned char cipher[MAX_JSON_MESSAGE_SIZE];
    unsigned char* message_uc  = (unsigned char*)(message.to_str().c_str());
    std::copy (aes_key.begin(), aes_key.end(), key_c);
    key_c[aes_key.length()] = 0;
    Debug().info ("Key : ", key_c);
    Debug().info ("Normal Key : ", get_aes_token());
    Debug().info ("Message : ", message_uc);

    int len = crypto_unit->get_aes_ptr()->encrypt(message_uc, message.to_str().length(), key_c, cipher);
    Debug().warning ("In send_connect_verify ====> cipher len : ", len);
    send (sfd,  (char*)cipher, strlen((char*)(cipher)), NULL);
    return;
}

CustomerModel::~CustomerModel()
{

}
