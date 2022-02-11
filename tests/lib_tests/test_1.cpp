#include <gtest/gtest.h>
#include <random>
#include <string>
#include <algorithm>
#include <openssl/evp.h>
#include "../../lib/include/util/cyptolib/crypto_unit.h"

#define TEST_COMPLICATION 150


/*Function for random string generating*/
std::string random_string()
{
     std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

     std::random_device rd;
     std::mt19937 generator(rd());

     std::shuffle(str.begin(), str.end(), generator);

     return str.substr(0, 32);    // assumes 32 < number of characters in str         
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
    RSA* rsa = EVP_PKEY_get1_RSA(pkey);
    BIO* keybio = BIO_new(BIO_s_mem());


    RSA_print(keybio, rsa, 0);
    char buffer [1024];
    std::string res = "";
    while (BIO_read (keybio, buffer, 1024) > 0)
    {
        res += buffer;
    }
    BIO_free(keybio); //appropriate free "method"
    RSA_free(rsa);

    return (bool)res.length();
}


/*TEST SECTION*/
TEST(Test1, KeyGenTest) 
{
        RSA_Unit rsau;
        char* str = strdup(random_string().c_str());
        EVP_PKEY* pkey = rsau.Generate_KeyPair_Ex(str);
        int res = -1;
        if (pkey)
        {
            res = 0;
        }
        else
        {
            res = 1;
        }

        EXPECT_EQ(0, res);

        EVP_PKEY_free(pkey);
        delete[] str;
}


TEST(Test2, KeyGenTest) 
{
        RSA_Unit rsau;
        char* str = strdup(random_string().c_str());
        EVP_PKEY* pkey = rsau.Generate_KeyPair_Ex(str);
        int res = -1;
        if (pkey)
        {
            res = 0;
        }
        else
        {
            res = 1;
        }

        EXPECT_EQ(0, res);

        EVP_PKEY_free(pkey);
        delete[] str;
}

TEST(Test3, KeyGenTest) 
{
        RSA_Unit rsau;
        char* str = strdup(random_string().c_str());
        EVP_PKEY* pkey = rsau.Generate_KeyPair_Ex(str);
        int res = -1;

        if (pkey) res = 0;
    
        else res = 1;
        
        EXPECT_EQ(0, res);
        EVP_PKEY_free(pkey);
        delete[] str;
}


TEST(TestReadPublicKey, KeyGenTestFileSystemREAD) 
{
    Debug::disable_debug();
    char* priv_file_name = "Private.key";
    char* pub_file_name = "Public.key";
    EVP_PKEY* pubkey = nullptr;

    RSA_Unit rsau;
    char* str = strdup(random_string().c_str());
    int res = rsau.Generate_KeyPair_Im(str, 
                                        pub_file_name, 
                                            priv_file_name);
    
    
    pubkey = rsau.ReadPubKey_FromFile(pub_file_name);
    // EXPECT_EQ (true, validate_pkey(pubkey));
    
    EVP_PKEY_free(pubkey);

    delete[] str; 
}


TEST(TestReadPrivateKey, KeyGenTestFileSystemREAD) 
{
    char* priv_file_name = "Private.key";
    char* pub_file_name = "Public.key";
    EVP_PKEY* privkey = nullptr;

    RSA_Unit rsau;
    char* str = strdup(random_string().c_str());
    int res = rsau.Generate_KeyPair_Im(str, 
                                        pub_file_name, 
                                            priv_file_name);
    
    privkey = rsau.ReadPrivKey_FromFile(priv_file_name, str);
    EXPECT_EQ (true, validate_pkey(privkey));

    EVP_PKEY_free(privkey);

    delete[] str; 
}


int main(int argc, char* argv[])
{     
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}