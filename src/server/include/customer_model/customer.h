#ifndef __CUSTOMER_H__
#define __CUSTOMER_H__
#include "customer_crypto_unit.h"

namespace Customer
{
    class CustomerModel
    {
        public:
            CustomerModel (int sfd);
            ~CustomerModel ();
            Security::CustomerCryptoUnit* get_crypto_unit(void);
        private:
            Security::CustomerCryptoUnit* crypto_unit;
            int sfd;

    };
};

#endif //__CUSTOMER_H__