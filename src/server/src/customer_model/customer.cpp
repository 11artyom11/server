#include "../../include/customer_model/customer.h"

using namespace Customer;

CustomerModel::CustomerModel(int sfd) :
    sfd{sfd}
{
    crypto_unit = new Security::CustomerCryptoUnit(sfd);
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
