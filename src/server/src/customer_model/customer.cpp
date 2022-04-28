#include <customer.h>

using namespace Customer;

CustomerModel::CustomerModel(int sfd, 
                                const std::string& unique_token) :
    sfd{sfd},
    unique_token{unique_token}
{
    Debug().info("Retrieved data SFD : ", sfd, " UNIQUE TOKEN : ", unique_token);
    crypto_unit = std::make_unique<Security::CustomerCryptoUnit>(Security::CustomerCryptoUnit( sfd));
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
    this->aes_token = token;
    return;
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

CustomerModel::~CustomerModel()
{

}
