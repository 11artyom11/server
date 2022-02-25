#ifndef __CUSTOMER_H__
#define __CUSTOMER_H__
#include "customer_crypto_unit.h"
#include <random>
#include <string>
#include <algorithm>


namespace Customer
{
    class CustomerModel
    {
        public:
            CustomerModel (int sfd, const std::string& unique_token);
            ~CustomerModel ();
            int get_sfd (void) const noexcept;
            Security::CustomerCryptoUnit* get_crypto_unit(void);
        private:
            Security::CustomerCryptoUnit* crypto_unit;
            std::string unique_token;
            int sfd;

    };
};

#endif //__CUSTOMER_H__