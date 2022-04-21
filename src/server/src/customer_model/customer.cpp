#include <customer.h>

using namespace Customer;

CustomerModel::CustomerModel(int sfd, 
                                const std::string& unique_token, 
                                    const Security::RSA_Keypair_shrd_ptr& kp) :
    sfd{sfd},
    unique_token{unique_token}
{
    Debug().info("Retrieved data SFD : ", sfd, " UNIQUE TOKEN : ", unique_token);
    crypto_unit = std::make_unique<Security::CustomerCryptoUnit>(Security::CustomerCryptoUnit( keypair, sfd));
    keypair = kp;
}

int CustomerModel::get_sfd(void) const noexcept
{
    return this->sfd;
}

CustomerModel::~CustomerModel()
{

}

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
