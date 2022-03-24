#include "../../../include/util/cyptolib/crypto_unit.h"

/*
+---------------------------------------------------+
|              class BaseCipherUnit                 |
+---------------------------------------------------+
*/

/**
 * @brief Returns Content of given file in the way it is
 *
 * @param filename Name of file
 * @return char*
 */
char *BaseCipherUnit::get_file_content(char *filename)
{

    FILE *f = fopen(filename, "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET); /* same as rewind(f); */

    char *str = (char *)malloc(fsize + 1);
    fread(str, fsize, 1, f);
    fclose(f);

    str[fsize] = 0;
    return str;
}

/*
+---------------------------------------------------+
|              class RSA_Unit                       |
+---------------------------------------------------+
*/

/**
 * @brief Returns public key in EVP_PKEY struct
 *
 * @param filename name of file
 */
EVP_PKEY *RSA_Unit::ReadPubKey_FromFile(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
        return nullptr;

    EVP_PKEY *key = EVP_PKEY_new();
    if (key)
    {
        EVP_PKEY_assign_RSA(key, PEM_read_RSA_PUBKEY(fp, NULL, NULL, NULL));
    }

    fclose(fp);
    return key;
}

/**
 * @brief returns a private key in EVP_PKEY struct
 *
 * @param filename name of file
 * @param passphrase password required to access pure private key
 */
EVP_PKEY *RSA_Unit::ReadPrivKey_FromFile(char *filename, char *passphrase)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
        return nullptr;

    EVP_PKEY *key = EVP_PKEY_new();

    if (key)
    {
        EVP_PKEY_assign_RSA(key, PEM_read_RSAPrivateKey(fp, NULL, NULL, passphrase));
    }

    fclose(fp);
    return key;
}

/**
 * @brief Generate and save
 * in filesystem key pair for RSA key agreement
 *
 * @param pass
 * @return RSA*
 */
EVP_PKEY *RSA_Unit::Generate_KeyPair(char *pass)
{

    char rand_buff[16];
    EVP_PKEY *pkey = NULL;
    RSA *r;

    int bits = 1024;            //      512, 1024, 2048, 4096
    unsigned long exp = RSA_F4; //      RSA_3
    OpenSSL_add_all_algorithms();

    RAND_load_file("/dev/urandom", 1024); // RAND_seed(rand_buff, 16); On linux: RAND_load_file("/dev/urandom", 1024);
    r = RSA_generate_key(bits, exp, NULL, NULL);

    if (RSA_check_key(r) != 1)
    ;
    ;
    ; 
    // Check key - error out

    // Create EVP to save to file.
    pkey = EVP_PKEY_new();

    EVP_PKEY_set1_RSA(pkey, r);

    RSA_free(r);
    return pkey;
}

EVP_PKEY *RSA_Unit::Generate_KeyPair_Ex(char *pass)

{
    EVP_PKEY *pkey = this->Generate_KeyPair(pass);
    if (!pkey)
    {
        return nullptr;
    }
    return pkey;
}

/**
 * @brief Create RSA keypair and write them into 
 * files
 * 
 * @param pass password for private key
 * @param pub_key_name  filename for public key
 * @param priv_key_name  filename for privaye key
 * @return int 
 */
int RSA_Unit::Generate_KeyPair_Im(char *pass,
                                  char *pub_key_name,
                                  char *priv_key_name)
{
    Debug().info("In function RSA_Unit::Generate_KeyPair_Im");
    EVP_PKEY *pkey = this->Generate_KeyPair(pass);

    if (!pkey)
    {
        Debug().fatal("Failed to create key pair...");
        return 1;
    }
    Debug().info(pub_key_name, " | ", priv_key_name);
    // //Save private key
    FILE *fp = fopen(priv_key_name, "w");

    if (fp == nullptr)
    {
        Debug().fatal("Failed to open  file for private key");
        return 1;
    }
    int res = PEM_write_PrivateKey(fp, pkey, EVP_aes_256_cbc(), NULL, 0, NULL, pass);
    if (res == 0)
    {
        Debug().fatal("Failed to write private key to file");
    }
    fclose(fp);

    // Save public key
    fp = fopen(pub_key_name, "w");
    if (!fp)
    {
        Debug().fatal("Failed to create public key  file");
        return 1;
    }

    res = PEM_write_PUBKEY(fp, pkey);
    if (res == 0)
    {
        Debug().fatal("Failed to write public key to file");
    }

    if (fclose(fp))
    {
        Debug().fatal ("Something gone wrong while closing file...");
        exit(-1);
    }
    EVP_PKEY_free(pkey);

    Debug().info("Out of function RSA_Unit::Generate_KeyPair_Im");
    return 0;
}

/**
 * @brief Encrypt given raw unencrtpted string and
 * encrypt with public key;
 *
 * @param raw_str unencrtpted string
 * @param pub_key public key
 * @return encrypted string
 */
char *RSA_Unit::rsa_encrypt(char *raw_str,
                            char *key)
{
    BIO *bio = BIO_new_mem_buf((void *)key, strlen(key));
    RSA *rsa = PEM_read_bio_RSA_PUBKEY(bio, NULL, NULL, NULL);
    BIO_free(bio);

    uint64_t len = strlen(raw_str);
    unsigned char *encrypted_str = (unsigned char *)malloc(RSA_size(rsa));

    int result = RSA_public_encrypt(len,
                                    (const unsigned char *)(raw_str),
                                    encrypted_str,
                                    rsa,
                                    RSA_PKCS1_OAEP_PADDING);

    RSA_free(rsa);

    return (char *)encrypted_str;
}

/**
 * @brief Encrypt given C string with key
 * 
 * @param raw_str C string to be encrypted
 * @param key Rsa key
 * @return char* 
 */
char *RSA_Unit::rsa_encrypt(char *raw_str,
                            RSA *key)
{
    uint64_t len = strlen(raw_str);

    unsigned char *encrypted_str = (unsigned char *)malloc(RSA_size(key));

    int result = RSA_public_encrypt(len,
                                    (const unsigned char *)(raw_str),
                                    encrypted_str,
                                    key,
                                    RSA_PKCS1_OAEP_PADDING);
    return (char *)encrypted_str;
}

/**
 * @brief Encrypt given encrtpted string and
 * decrypt with private key;
 *
 * REQUIRES INPUTTING PASSPHRASE FOR PRIVATE KEYS
 * use alternative function with RSA* instead
 *
 * @param raw_str encrtpted string
 * @param pub_key private key
 * @return decrypted string
 */
char *RSA_Unit::rsa_decrypt(char *enc_str,
                            char *key)
{
    BIO *bio = BIO_new_mem_buf((void *)key, strlen(key));
    RSA *rsa = PEM_read_bio_RSAPrivateKey(bio, NULL, NULL, NULL);
    BIO_free(bio);
    int slen = RSA_size(rsa);
    unsigned char *decrypted_str = (unsigned char *)malloc(RSA_size(rsa));
    int retval = RSA_private_decrypt(slen,
                                     (const unsigned char *)enc_str,
                                     decrypted_str,
                                     rsa,
                                     RSA_PKCS1_OAEP_PADDING);

    RSA_free(rsa);

    return (char *)decrypted_str;
}

/**
 * @brief Decrypt encrypted string passed as c string by
 * RSA* struct pointer
 * 
 * @param enc_str 
 * @param key 
 * @return char* 
 */
char *RSA_Unit::rsa_decrypt(char *enc_str,
                            RSA *key)
{
    int slen = RSA_size(key);
    unsigned char *decrypted_str = (unsigned char *)malloc(RSA_size(key));
    int retval = RSA_private_decrypt(slen,
                                     (const unsigned char *)enc_str,
                                     decrypted_str,
                                     key,
                                     RSA_PKCS1_OAEP_PADDING);

    return (char *)decrypted_str;
}

/*
+---------------------------------------------------+
|              class AES_Unit                       |
+---------------------------------------------------+
*/

/**
 * @brief Generates random buffer whih represents AES key for further
 * encrpytion process
 *
 * @param len buffer size in Bytes
 * @return unsigned*
 */
unsigned char *AES_Unit::generate_key(const uint16_t len)
{
    unsigned char *key = new unsigned char[len];
    if (!RAND_bytes(key, sizeof key))
    {
        Debug().fatal("Something gone wrong in generating keys");
    }
    return key;
}

/**
 * @brief Encrypt plain text stored in $from and saves it in $to
 * Encryption is done using key $key
 *
 *
 *  * This function is used to encrypt allowed maximum chunk size 16
 *
 *
 * @param from source
 * @param key AES key for encrpytion
 * @param to  destination
 * @return 0 on success -1 on failure
 */
int AES_Unit::encrypt (unsigned char* text, int text_len, const  unsigned char* key, unsigned char* cipher)
{
    int cipher_len = 0;
    int len = 0;
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    if (!ctx)
    {
        Debug().fatal("EVP_CIPHER_CTX_new(); failed");
        exit(-1);
    }

    if (!EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb    (), NULL, key, NULL))
    {
        Debug().fatal("EVP_EncryptInit_ex() failed");
        exit(-1);
    }

    if (!EVP_EncryptUpdate(ctx, cipher, &len, text, text_len))
    {
        Debug().fatal("EVP_EncryptUpdate() failed");
        exit(-1);
    }

    cipher_len += len;
    
    if (!EVP_EncryptFinal_ex(ctx, cipher + len, &len))
    {
        Debug().fatal("Final_ex failed");       
        exit(-1);
    }
   
   cipher_len += len;

   EVP_CIPHER_CTX_free(ctx);
   return cipher_len;
}

/**
 * @brief Decrypt encrypted data stored in $from and saves it in $to
 * Decryption is done using key $key
 *
 * This function is used to decrypt allowed maximum chunk size 16
 *
 * @param from source
 * @param key AES key for Decrpytion
 * @param to  destination
 * @return 0 on success -1 on failure
 */
int AES_Unit::decrypt(unsigned char* cipher, int cipher_len,  unsigned char* key, unsigned char* text)
{
    int text_len = 0;
    int len = 0;
    
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    if (!ctx)
    {
        Debug().fatal("ctx errror");
        exit(-1);
    }

    if (!EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL))
    {
        Debug().fatal("init error");
        exit(-1);
    }

    if (!EVP_DecryptUpdate(ctx, text, &len, cipher, cipher_len))
    {
        Debug().fatal("update error");
        exit(-1);
    }

    text_len += len;
    
    if (!EVP_DecryptFinal_ex(ctx, text + len, &len))
    {
        Debug().fatal("final error");
        exit(-1);
    }

    text_len += len;

    EVP_CIPHER_CTX_free(ctx);
    return text_len;
}
