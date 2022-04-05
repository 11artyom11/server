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
#include <openssl/aes.h>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <cstdint>

#include <mutex>
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


std::string string_to_hex(const std::string& in);
std::string hex_to_string(const std::string& in);
char *base64encode (const void *b64_encode_this, int encode_this_many_bytes);
char *base64decode (const void *b64_decode_this, int decode_this_many_bytes);

/*Base class for cipher node of project*/
class BaseCipherUnit
{
public:
    BaseCipherUnit()    = default;
    ~BaseCipherUnit()   = default;

  
    static char* get_file_content(char* filename);

};


class RSA_Unit : public BaseCipherUnit
{
    public:
            /*
        About EVP_PKEY structure 
        https://www.openssl.org/docs/man3.0/man3/EVP_PKEY.html
        */
        static EVP_PKEY* ReadPubKey_FromFile  (char* filename);
        static EVP_PKEY* ReadPrivKey_FromFile (char* filename, char* passphrase = nullptr);

        EVP_PKEY* Generate_KeyPair_Ex(char* pass);
        int Generate_KeyPair_Im(char* pass, 
                                    char* pub_key_name,
                                        char* priv_key_name);
        /*Encrypt Decrypt function overloaded versions with std::string*/
         unsigned char* rsa_encrypt (const unsigned char* raw_str,
                                char* key);
         unsigned char* rsa_encrypt (const unsigned char* raw_str,
                                RSA* key);
        char* rsa_decrypt (char* enc_str, 
                                char* key);
        char* rsa_decrypt (char* enc_str, 
                                RSA* key);
                                        
    private:
         EVP_PKEY* Generate_KeyPair(char* pass);
};


class AES_Unit : public BaseCipherUnit
{
    public:
        unsigned char* generate_key (const uint16_t len = 16);
        int encrypt (unsigned char* text, int text_len, const  unsigned char* key, unsigned char* cipher);
        int decrypt (unsigned char* cipher, int cipher_len,   unsigned char* key, unsigned char* text);
    
};
#endif // __CRYPTO_UNIT_H__