#ifndef __CUSTOMER_CRYPTO_UNIT_H__
#define __CUSTOMER_CRYPTO_UNIT_H__

#include "../../../../lib/include/util/cyptolib/crypto_unit.h"
#include <map>
#include <algorithm>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
namespace Security
{
    class CustomerCryptoUnit;
    struct RSA_UNAR_KEY;

    typedef std::pair <RSA_UNAR_KEY, Security::RSA_UNAR_KEY> RSA_Keypair;

    /*singleton struct to generate key <<unions>> */
    struct RSA_UNAR_KEY
    {
        EVP_PKEY* evp_key;
        char* c_key;

        ~RSA_UNAR_KEY () 
        {
            // EVP_PKEY_free (evp_key);
            // delete c_key;
        }
    };

    class CustomerCryptoUnit
    {
        public:
            /*Model of this class allows only to generate or/and assign server side keypair*/
            /*And only assign client public key*/
            CustomerCryptoUnit (int sfd = 0);

            ~CustomerCryptoUnit ();
            /*Generate and assign RSA keypair for server side*/
            int init_server_keypair (char* passphrase = nullptr);

            /*Set already existing RSA_Keypair (typedef) to model*/
            int set_server_keypair (const RSA_Keypair& __other);

            /*Set retrieved cliend-created public RSA key*/
            int set_client_key (const RSA_UNAR_KEY& __other);

            /*Return RSA_Keypair of $this model*/
            RSA_Keypair& get_server_keypair (void);

            /*Return RSA_UNAR_KEY of $this model*/
            RSA_UNAR_KEY& get_client_key (void);
            
        private:
        /*Key-pair which has been generated on server side*/
            RSA_Keypair server_keypair;

        /*Key which has been retrieved from client side*/
            RSA_UNAR_KEY client_keypair;

        /*Unique token (int) yet is sfd of connection as 
            one connection can be hold by only and only one customer*/
            char* c_sfd;
    };
    
}

#endif //__CUSTOMER_CRYPTO_UNIT_H__