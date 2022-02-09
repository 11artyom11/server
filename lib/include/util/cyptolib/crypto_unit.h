#ifndef __CRYPTO_UNIT_H__
#define __CRYPTO_UNIT_H__

#include "../../helpers/debug_helper/debug_helper.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/objects.h>
#include <openssl/x509.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/engine.h>
#include <openssl/rand.h>
#include <string>

/*
Enum which describes way of generating key pair
*/
enum class INIT_TYPE
{
    //Stream type which means no concerning filesystem
    STREAM_,

    //save pairs in filesystem
    FILE_
};

/*Base class for cipher node of project*/
class BaseCipherUnit
{
public:
    BaseCipherUnit() = default;
    ~BaseCipherUnit() = default;

    /*
    About EVP_PKEY structure 
    https://www.openssl.org/docs/man3.0/man3/EVP_PKEY.html
    */
    static EVP_PKEY* ReadPubKey_FromFile(char* filename);
    static EVP_PKEY* ReadPrivKey_FromFile(char* filename);
};


class RSA_Unit : public BaseCipherUnit
{
    public:
        RSA_Unit() = default;
        ~RSA_Unit() = default;

   
        int Generate_KeyPair_Ex(char* pass, EVP_PKEY* pkey);
        int Generate_KeyPair_Im(char* pass, 
                                    char* pub_key_name,
                                        char* priv_key_name);
        
        int init_keys (void);

    private:

         EVP_PKEY* Generate_KeyPair(char* pass);
};
#endif // __CRYPTO_UNIT_H__