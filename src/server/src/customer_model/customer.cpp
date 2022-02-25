#include "../../include/customer_model/customer.h"

using namespace Customer;

CustomerModel::CustomerModel(int sfd, 
                                const std::string& unique_token) :
    sfd{sfd},
    unique_token{unique_token}
{
    Debug().info("Retrieved data SFD : ", sfd, " UNIQUE TOKEN : ", unique_token);
    crypto_unit = new Security::CustomerCryptoUnit(sfd);
}

int CustomerModel::get_sfd(void) const noexcept
{
    return this->sfd;
}

CustomerModel::~CustomerModel()
{
    delete this->crypto_unit;
}

/**
 * @brief Return crpytounit
 * 
 * @return Security::CustomerCryptoUnit* 
 */
Security::CustomerCryptoUnit* CustomerModel::get_crypto_unit(void)
{
    return this->crypto_unit;
}
