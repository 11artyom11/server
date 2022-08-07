#include "cyptolib/crypto_unit.h"

char *base64encode(const void *b64_encode_this, int encode_this_many_bytes) {
  BIO *b64_bio,
      *mem_bio;  // Declares two OpenSSL BIOs: a base64 filter and a memory BIO.
  BUF_MEM *mem_bio_mem_ptr;  // Pointer to a "memory BIO" structure holding our
                             // base64 data.
  b64_bio = BIO_new(BIO_f_base64());  // Initialize our base64 filter BIO.
  mem_bio = BIO_new(BIO_s_mem());     // Initialize our memory sink BIO.
  BIO_push(b64_bio,
           mem_bio);  // Link the BIOs by creating a filter-sink BIO chain.
  BIO_set_flags(
      b64_bio,
      BIO_FLAGS_BASE64_NO_NL);  // No newlines every 64 characters or less.
  BIO_write(b64_bio, b64_encode_this,
            encode_this_many_bytes);  // Records base64 encoded data.
  BIO_flush(b64_bio);  // Flush data.  Necessary for b64 encoding, because of
                       // pad characters.
  BIO_get_mem_ptr(
      mem_bio,
      &mem_bio_mem_ptr);  // Store address of mem_bio's memory structure.
  BIO_set_close(
      mem_bio,
      BIO_NOCLOSE);       // Permit access to mem_ptr after BIOs are destroyed.
  BIO_free_all(b64_bio);  // Destroys all BIOs in chain, starting with b64 (i.e.
                          // the 1st one).
  BUF_MEM_grow(mem_bio_mem_ptr,
               (*mem_bio_mem_ptr).length + 1);  // Makes space for end null.
  (*mem_bio_mem_ptr).data[(*mem_bio_mem_ptr).length] =
      '\0';  // Adds null-terminator to tail.
  return (*mem_bio_mem_ptr)
      .data;  // Returns base-64 encoded data. (See: "buf_mem_st" struct).
}

char *base64decode(const void *b64_decode_this, int decode_this_many_bytes) {
  BIO *b64_bio,
      *mem_bio;  // Declares two OpenSSL BIOs: a base64 filter and a memory BIO.
  char *base64_decoded = (char *)calloc((decode_this_many_bytes * 3) / 4 + 1,
                                        sizeof(char));  //+1 = null.
  b64_bio = BIO_new(BIO_f_base64());  // Initialize our base64 filter BIO.
  mem_bio = BIO_new(BIO_s_mem());     // Initialize our memory source BIO.
  BIO_write(mem_bio, b64_decode_this,
            decode_this_many_bytes);  // Base64 data saved in source.
  BIO_push(b64_bio,
           mem_bio);  // Link the BIOs by creating a filter-source BIO chain.
  BIO_set_flags(b64_bio,
                BIO_FLAGS_BASE64_NO_NL);  // Don't require trailing newlines.
  int decoded_byte_index =
      0;  // Index where the next base64_decoded byte should be written.
  while (0 < BIO_read(b64_bio, base64_decoded + decoded_byte_index,
                      1)) {  // Read byte-by-byte.
    decoded_byte_index++;  // Increment the index until read of BIO decoded data
                           // is complete.
  }  // Once we're done reading decoded data, BIO_read returns -1 even though
     // there's no error.
  BIO_free_all(b64_bio);  // Destroys all BIOs in chain, starting with b64 (i.e.
                          // the 1st one).
  return base64_decoded;  // Returns base-64 decoded data with trailing null
                          // terminator.
}

/**
 * @brief Returns the nearest multiple of the
 * given integer
 *
 * @param n given integer
 * @param multiple
 * @return int nearest multiple of $multiple
 */
int round(int n, int multiple) {
  // Smaller multiple
  int a = (n / multiple) * multiple;

  // Larger multiple
  int b = a + multiple;

  // Return of closest of two
  return (n - a > b - n) ? b : a;
}

/**
 * @brief Helper function to convert raw string to hex string
 *
 * @param in
 * @return std::string
 */
std::string string_to_hex(const std::string &in) {
  std::stringstream ss;
  ss << std::hex << std::setfill('0');
  for (size_t i = 0; in.length() > i; ++i) {
    ss << std::setw(2)
       << static_cast<unsigned int>(static_cast<unsigned char>(in[i]));
  }

  return ss.str();
}

/**
 * @brief Helper function to convert hex string to raw string
 *
 * @param in
 * @return std::string
 */
std::string hex_to_string(const std::string &in) {
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
char *BaseCipherUnit::get_file_content(char *filename) {
  FILE *f = fopen(filename, "rb");
  if (!f) {
    Debug().fatal("File does not exist");
    return nullptr;
  }
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
 * @brief Init public key and store it in the object scope
 *
 * @return 1 on failure 0 on success
 */
int RSA_Unit::init_public_key(unsigned char *key) __THROW {
  /*ref : RSA_Unit::createRSA(...)*/
  this->public_key.reset(create_RSA(key, 1), RSA_free);
  Debug().info("INIT RESULT : ", (public_key != nullptr ? 0 : 1));
  return (public_key != nullptr ? 0 : 1);
}

/**
 * @brief Init private key and store it in the object scope
 * @return 1 on failure 0 on success
 */
int RSA_Unit::init_private_key(unsigned char *key) __THROW {
  /*ref : RSA_Unit::createRSA(...)*/
  this->private_key.reset(create_RSA(key, 0), RSA_free);
  return (private_key != nullptr ? 0 : 1);
}

/**
 * @brief Init both public and private keys
 *
 * @return 1 on failure 0 on success
 */
int RSA_Unit::init_keys(unsigned char *pr_key, unsigned char *pub_key) __THROW {
  return init_private_key(pr_key) | init_public_key(pub_key);
}

/**
 * @brief Usage for public key: createRSA(“PUBLIC_KEY_BUFFER”,1);
        Usage for private key: createRSA(“PRIVATE_KEY_BUFFER”,0);
 *
 * @param key
 * @param public
 */
RSA *RSA_Unit::create_RSA(unsigned char *key, int is_public) {
  RSA *rsa = NULL;
  BIO *keybio;
  keybio = BIO_new_mem_buf(key, -1);
  if (keybio == NULL) {
    printf("Failed to create key BIO");
    return 0;
  }
  if (is_public) {
    rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);
  } else {
    rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);
  }
  Debug().info("RSA INSTANCE : ", rsa);
  return rsa;
}

/**
 * @brief  use this function to create RSA with key file name
 *
 * @param filename
 * @param public
 */
RSA *RSA_Unit::create_RSA_with_filename(char *filename, int is_public)

{
  FILE *fp = fopen(filename, "rb");

  if (fp == NULL) {
    printf("Unable to open file %s \n", filename);
    return NULL;
  }
  RSA *rsa = RSA_new();

  if (is_public) {
    rsa = PEM_read_RSA_PUBKEY(fp, &rsa, NULL, NULL);
  } else {
    rsa = PEM_read_RSAPrivateKey(fp, &rsa, NULL, NULL);
  }

  return rsa;
}

/**
 * @brief Encrypt passed data with public key
 *
 * @note public key MUST BE initialized before
 * using this function
 * @note assert is standing at the top of function
 * to prevent uninitialized trial of public encrypt
 *
 * @param data Data to be encrypted
 * @param data_len Length of data
 * @param key RSA* struct pointer (initted)
 * @param encrypted Array where result will be stored
 * @return -1 on error
 */
int RSA_Unit::public_encrypt(unsigned char *data, int data_len,
                             unsigned char *encrypted) {
  assert(public_key != nullptr);
  int result =
      RSA_public_encrypt(data_len, data, encrypted, public_key.get(), padding);
  return result;
}

/**
 * @brief Decrypt passed data with private key
 *
 * @note public key MUST BE initialized before
 * using this function
 * @note assert is standing at the top of function
 * to prevent uninitialized trial of public encrypt
 *
 * @param enc_data Data to be decrypted
 * @param data_len Length of encrypted data
 * @param key Private key (initted)
 * @param decrypted Array where decrypted data will be stored
 * @return -1 on failure
 */
int RSA_Unit::private_decrypt(unsigned char *enc_data, int data_len,
                              unsigned char *decrypted) {
  assert(private_key != nullptr);
  int result = RSA_private_decrypt(data_len, enc_data, decrypted,
                                   private_key.get(), padding);
  return result;
}

RSA_Unit::~RSA_Unit() {
  // RSA_free (public_key);
  // RSA_free (private_key);
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
unsigned char *AES_Unit::generate_key(const uint16_t len) {
  unsigned char *key = new unsigned char[len];
  if (!RAND_bytes(key, len)) {
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
int AES_Unit::encrypt(unsigned char *text, int text_len,
                      const unsigned char *key, unsigned char *cipher) {
  int cipher_len = 0;
  int len = 0;
  EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

  if (!ctx) {
    Debug().fatal("EVP_CIPHER_CTX_new(); failed");
    throw;
  }

  if (!EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL)) {
    Debug().fatal("EVP_EncryptInit_ex() failed");
    throw;
  }

  if (!EVP_EncryptUpdate(ctx, cipher, &len, text, text_len)) {
    Debug().fatal("EVP_EncryptUpdate() failed");
    throw;
  }

  cipher_len += len;

  if (!EVP_EncryptFinal_ex(ctx, cipher + len, &len)) {
    Debug().fatal("Final_ex failed");
    throw;
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
int AES_Unit::decrypt(unsigned char *cipher, int cipher_len, unsigned char *key,
                      unsigned char *text) {
  int text_len = 0;
  int len = 0;

  EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

  if (!ctx) {
    Debug().fatal("ctx errror");
    throw;
  }

  if (!EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL)) {
    Debug().fatal("init error");
    throw;
  }

  if (!EVP_DecryptUpdate(ctx, text, &len, cipher, cipher_len)) {
    Debug().fatal("update error");
    throw;
  }

  text_len += len;

  if (!EVP_DecryptFinal_ex(ctx, text + len, &len)) {
    Debug().fatal("final error");
    throw;
  }

  text_len += len;

  EVP_CIPHER_CTX_free(ctx);
  return text_len;
}

void AES_Unit::set_key(const std::string &key) {
  this->key = key;
  return;
}

std::string AES_Unit::get_key(void) const noexcept { return this->key; }
