/**
 * @file customer.h
 * @author Artyom Grigorian (grigorianartyom1@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-23
 * @section DESCRIPTION
 * This class is made to add abstract level to customer 
 * model on server side
 * 
 * @section Last Changes 23-03-2022 Artyom Grigorian
 * Changed naked pointers into smart ones
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __CUSTOMER_H__
#define __CUSTOMER_H__
#include "customer_crypto_unit.h"
#include <random>
#include <string>
#include <algorithm>
#include <memory>

namespace Customer
{
    template <typename T>
    using shared_ptr = std::shared_ptr<T>;

    typedef shared_ptr<Security::CustomerCryptoUnit> \
                 CustomerCryptoUnit_shrd_ptr;

    class CustomerModel
    {
        public:
            CustomerModel (int sfd, const std::string& unique_token, const Security::RSA_Keypair_shrd_ptr&);
            ~CustomerModel ();
            int get_sfd (void) const noexcept;
            void set_aes_token (const std::string& token);
            Security::CustomerCryptoUnit* get_crypto_unit(void);
        private:
            CustomerCryptoUnit_shrd_ptr crypto_unit;
            Security::RSA_Keypair_shrd_ptr keypair;
            std::string unique_token;
            std::string aes_token;
            int sfd;

    };
};

#endif //__CUSTOMER_H__