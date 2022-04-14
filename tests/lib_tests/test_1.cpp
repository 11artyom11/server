#include <gtest/gtest.h>
#include <random>
#include <string>
#include <algorithm>
#include <openssl/evp.h>
#include "../../lib/include/util/cyptolib/crypto_unit.h"

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

/*TEST SECTION*/
TEST(Test1, KeyGenTest)
{
        RSA_Unit rsau;
        char* str = strdup(random_string().c_str());
        EVP_PKEY* pkey = rsau.Generate_KeyPair_Ex(str);
        int res = -1;

        if (pkey) res = 0;
        else  res = 1;;;;

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
        if (pkey) res = 0;
        else  res = 1;;;;

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
        else res = 1;;;;

        EXPECT_EQ(0, res);
        EVP_PKEY_free   (pkey);
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
    EXPECT_EQ (true, validate_pkey(pubkey));

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

TEST(ENCRYPT_DECRYPT_RSA_STRUCT_FUNCTIONS, ENCRYPT_DECRYPT_TEST)
{
    RSA_Unit rsaU;
    rsaU.Generate_KeyPair_Im("a", "Public.key", "Private.key");
    EVP_PKEY *pubkey = rsaU.ReadPubKey_FromFile("Public.key");
    RSA *rsa_e =  EVP_PKEY_get1_RSA(pubkey);
    
    EVP_PKEY *privkey = rsaU.ReadPrivKey_FromFile("Private.key", "a");
    RSA *rsa_d = EVP_PKEY_get1_RSA(privkey);

    unsigned char* es;
    char* ds;
    for (int times = 0; times < TEST_COMPLICATION; times++)
    {
        unsigned char* rand_str = (unsigned char*)random_string().c_str();
    /*Encrypt*/
        es = rsaU.rsa_encrypt(rand_str, rsa_e);
        
    /*Decrypt*/
        ds = rsaU.rsa_decrypt((char*)es, rsa_d);
    
        EXPECT_EQ(0, strcmp((char*)rand_str, ds));
        delete[] es;
        delete[] ds;
    }

    EVP_PKEY_free(pubkey);
    EVP_PKEY_free(privkey);

    RSA_free(rsa_e);
    RSA_free(rsa_d);
}



TEST(ENCRYPT_DECRYPT_C_STRING_KEYS, ENCRYPT_DECRYPT_TEST)
{
    RSA_Unit rsaU;
    rsaU.Generate_KeyPair_Im("a", "Public.key", "Private.key");
    char* pubkey = BaseCipherUnit::get_file_content("Public.key");
    char* privkey = BaseCipherUnit::get_file_content("Private.key");
    unsigned char* es;
    char* ds;
    // for (auto i = 0; i < TEST_COMPLICATION; ++i)
    {
        unsigned char* rand_str = (unsigned char*)"ABCDEF123456";
        /*Encrypt*/
        es = rsaU.rsa_encrypt(rand_str, pubkey);
            /*Decrypt*/
        ds = rsaU.rsa_decrypt((char*)es, privkey);
        
        Debug().info (rand_str, " :: ", ds);
        EXPECT_EQ(0, strcmp((char*)rand_str, ds));
    
    }
    
    delete[] es;
    delete[] ds;
    delete[] pubkey;
    delete[] privkey;
}

TEST (AES_ENCRYPT_DECRYPT, AES_UNIT)
{
    AES_Unit aes;
    const int ENC_STD = 128;
    const int STD_TXT_SIZE = 128;
    unsigned char *key = aes.generate_key(128);

    for (int times  = 1; times < 10+1; times++)
    {
        unsigned char  *text;
        text = new unsigned char [STD_TXT_SIZE];  
        
        strcat((char*)text, strdup(random_string().c_str()));
        int text_len = strlen((const char*)text);
        int buff_len = (text_len/ENC_STD + 1)*128;
        unsigned char *cipher = new unsigned char [buff_len];
        int cipher_len = aes.encrypt(text, text_len, key, cipher);
        unsigned char *decrypted = new unsigned char [buff_len]; 
        int dec_len = aes.decrypt(cipher, cipher_len, key, decrypted);
        
        char *hex_dec = new char [buff_len*2];
        char *hex_text = new char [buff_len*2];
        // Convert text to hex.
        for (int i = 0, j = 0; i < dec_len; ++i, j += 2)
        {
            sprintf(hex_dec + j, "%02x", decrypted[i] & 0xff);
            sprintf(hex_text + j, "%02x", text[i] & 0xff);
        }   
        EXPECT_EQ (0, strcmp(hex_text, hex_dec));

        delete[] cipher;
        delete[] decrypted;
        delete[] hex_text;
        delete[] hex_dec;
        delete[] text;
    }
    
    delete[] key;
}
int main(int argc, char *argv[])
{
    
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



