#include <gtest/gtest.h>
#include <random>
#include <string>
#include <algorithm>
#include <openssl/evp.h>
#include <crypto_unit.h>

#define TEST_COMPLICATION 100

/*Function for random string generating*/
std::string random_string(int len = 40)
{
    std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

    std::random_device rd;
    std::mt19937 generator(rd());

    std::shuffle(str.begin(), str.end(), generator);

    return str.substr(0, len); // assumes 32 < number of characters in str
}

/**
** Performs sanity checks on the given EVP_PKEY.
**
** Returns 1, 2, or 3 when valid:
**   - Returns 1 if only public key is present.
**   - Returns 2 if only private key is present.
**   - Returns 3 if both public and private keys are present.
**/
bool validate_pkey(EVP_PKEY *pkey)
{
    RSA *rsa = EVP_PKEY_get1_RSA(pkey);
    BIO *keybio = BIO_new(BIO_s_mem());

    RSA_print(keybio, rsa, 0);
    char buffer[1024];
    std::string res = "";
    while (BIO_read(keybio, buffer, 1024) > 0)
    {
        res += buffer;
    }
    BIO_free(keybio); // appropriate free "method"
    RSA_free(rsa);

    return (bool)res.length();
}




int main(int argc, char *argv[])
{
    
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



