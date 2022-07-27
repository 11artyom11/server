#include <gtest/gtest.h>
#include <random>
#include <string>
#include <algorithm>
#include <cassert>
#include <openssl/evp.h>
#include <crypto_unit.h>

#define TEST_COMPLICATION 10000000

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

TEST (RSA_1, RSA_TEST)
{
    RSA_Unit ru;
    unsigned char* pr_key = (unsigned char*)ru.get_file_content("Private.key");
    unsigned char* pb_key = (unsigned char*)ru.get_file_content("Public.key");

    ru.init_keys(pr_key, pb_key);

    unsigned char* data = (unsigned char*)"abcdefghijk12345678910253636";
    int data_len = strlen ((char*)data);
    unsigned char encrypted[1024];
    unsigned char decrypted[1024];
    int len = ru.public_encrypt (data, data_len, encrypted);
    ru.private_decrypt (encrypted, len, decrypted);
    Debug().info ("D MES : ", decrypted);

}

TEST (AES_TEST, AES_TEST)
{
    AES_Unit aes;
    unsigned char* key = (unsigned char*)("0123456789ABCDEF");
    unsigned char* text = (unsigned char*)("Red\0");
    unsigned char enc[1024];
    unsigned char dec[31];
    for (auto i = 0; i < TEST_COMPLICATION; ++i)
    {
         int len = aes.encrypt (text, strlen ((char*)text), key, enc);
        int testlen = strlen ((char*)enc);
        int ret_len = aes.decrypt (enc, len, key, dec);
        dec[ret_len] = '\0';
        EXPECT_EQ (0 , strcmp ((char*)text, (char*)dec));
    }
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



