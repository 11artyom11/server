#include "../../../include/util/cyptolib/crypto_unit.h"


char *base64encode (const void *b64_encode_this, int encode_this_many_bytes){
    BIO *b64_bio, *mem_bio;      //Declares two OpenSSL BIOs: a base64 filter and a memory BIO.
    BUF_MEM *mem_bio_mem_ptr;    //Pointer to a "memory BIO" structure holding our base64 data.
    b64_bio = BIO_new(BIO_f_base64());                      //Initialize our base64 filter BIO.
    mem_bio = BIO_new(BIO_s_mem());                           //Initialize our memory sink BIO.
    BIO_push(b64_bio, mem_bio);            //Link the BIOs by creating a filter-sink BIO chain.
    BIO_set_flags(b64_bio, BIO_FLAGS_BASE64_NO_NL);  //No newlines every 64 characters or less.
    BIO_write(b64_bio, b64_encode_this, encode_this_many_bytes); //Records base64 encoded data.
    BIO_flush(b64_bio);   //Flush data.  Necessary for b64 encoding, because of pad characters.
    BIO_get_mem_ptr(mem_bio, &mem_bio_mem_ptr);  //Store address of mem_bio's memory structure.
    BIO_set_close(mem_bio, BIO_NOCLOSE);   //Permit access to mem_ptr after BIOs are destroyed.
    BIO_free_all(b64_bio);  //Destroys all BIOs in chain, starting with b64 (i.e. the 1st one).
    BUF_MEM_grow(mem_bio_mem_ptr, (*mem_bio_mem_ptr).length + 1);   //Makes space for end null.
    (*mem_bio_mem_ptr).data[(*mem_bio_mem_ptr).length] = '\0';  //Adds null-terminator to tail.
    return (*mem_bio_mem_ptr).data; //Returns base-64 encoded data. (See: "buf_mem_st" struct).
}

char *base64decode (const void *b64_decode_this, int decode_this_many_bytes){
    BIO *b64_bio, *mem_bio;      //Declares two OpenSSL BIOs: a base64 filter and a memory BIO.
    char *base64_decoded =(char*) calloc( (decode_this_many_bytes*3)/4+1, sizeof(char) ); //+1 = null.
    b64_bio = BIO_new(BIO_f_base64());                      //Initialize our base64 filter BIO.
    mem_bio = BIO_new(BIO_s_mem());                         //Initialize our memory source BIO.
    BIO_write(mem_bio, b64_decode_this, decode_this_many_bytes); //Base64 data saved in source.
    BIO_push(b64_bio, mem_bio);          //Link the BIOs by creating a filter-source BIO chain.
    BIO_set_flags(b64_bio, BIO_FLAGS_BASE64_NO_NL);          //Don't require trailing newlines.
    int decoded_byte_index = 0;   //Index where the next base64_decoded byte should be written.
    while ( 0 < BIO_read(b64_bio, base64_decoded+decoded_byte_index, 1) ){ //Read byte-by-byte.
        decoded_byte_index++; //Increment the index until read of BIO decoded data is complete.
    } //Once we're done reading decoded data, BIO_read returns -1 even though there's no error.
    BIO_free_all(b64_bio);  //Destroys all BIOs in chain, starting with b64 (i.e. the 1st one).
    return base64_decoded;        //Returns base-64 decoded data with trailing null terminator.
}

/**
 * @brief Helper function to convert raw string to hex string
 * 
 * @param in 
 * @return std::string 
 */
std::string string_to_hex(const std::string& in) 
{
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (size_t i = 0; in.length() > i; ++i) {
        ss << std::setw(2) << static_cast<unsigned int>(static_cast<unsigned char>(in[i]));
    }

    return ss.str(); 
}

/**
 * @brief Helper function to convert hex string to raw string
 * 
 * @param in 
 * @return std::string 
 */
std::string hex_to_string(const std::string& in) {
    std::string output;

    if ((in.length() % 2) != 0) {
        throw std::runtime_error("String is not valid length ...");
    }

    size_t cnt = in.length() / 2;

    for (size_t i = 0; cnt > i; ++i) {
        uint32_t s = 0;
        std::stringstream ss;
        ss << std::hex << in.substr(i * 2, 2);
        ss >> s;

        output.push_back(static_cast<unsigned char>(s));
    }

    return output;
}

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
    int res = PEM_write_PrivateKey(fp, pkey, nullptr, NULL, 0, NULL, nullptr);
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
 unsigned char *RSA_Unit::rsa_encrypt(const unsigned char *raw_str,
                                        char *key)
{

    BIO *bio = BIO_new_mem_buf((void *)key, strlen(key));
    RSA *rsa = PEM_read_bio_RSA_PUBKEY(bio, NULL, NULL, NULL);
    BIO_free(bio);

    int len = strlen((const char*)raw_str);
    // Debug().info("Hello\n", strlen(key));
    // Debug().info("RSA SIZE ",RSA_size(rsa));

    unsigned char *encrypted_str = new unsigned char [RSA_size(rsa)];
    // memset(encrypted_str,'\0', RSA_size(rsa));
    // Debug().warning("len : ", len);
    // Debug().warning("raw_str : ", raw_str);
    // Debug().warning("encrypted_str : ", encrypted_str);
    // Debug().warning("rsa : ", rsa);
    int result = RSA_public_encrypt(len,
                                    raw_str,
                                    encrypted_str,
                                    rsa,
                                    RSA_PKCS1_OAEP_PADDING);
    // Debug().info ((result == -1 ? "ERRPR" : "OK ECIPHRT"));
    
    RSA_free(rsa);

    return encrypted_str;
}

/**
 * @brief 
 * 
 *
 * 
 * @param raw_str C string to be encrypted
 * @param key Rsa key
 * @return char* 
 */
 unsigned char *RSA_Unit::rsa_encrypt(const unsigned char *raw_str,
                            RSA *key)
{
    uint64_t len = strlen((const char*)raw_str);

    unsigned char *encrypted_str = (unsigned char *)malloc(RSA_size(key));

    int result = RSA_public_encrypt(len,
                                    raw_str,
                                    encrypted_str,
                                    key,
                                    RSA_PKCS1_OAEP_PADDING);
    return encrypted_str;
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
