#ifndef __CRYPTO_UNIT_H__
#define __CRYPTO_UNIT_H__

#include <openssl/aes.h>
#include <openssl/engine.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/objects.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <openssl/x509.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cassert>
#include <cstdint>
#include <iomanip>
#include <memory>
#include <mutex>
#include <sstream>
#include <stdexcept>

#include "../../helpers/debug_helper/debug_helper.h"

/*
Enum which describes way of generating key pair
*/
enum class INIT_TYPE {
  // Stream type which means no concerning filesystem
  STREAM_,

  // save pairs in filesystem
  FILE_
};

std::string string_to_hex(const std::string& in);
std::string hex_to_string(const std::string& in);
char* base64encode(const void* b64_encode_this, int encode_this_many_bytes);
char* base64decode(const void* b64_decode_this, int decode_this_many_bytes);

template <typename T>
using shared_ptr = std::shared_ptr<T>;

// function to round the number
int round(int n, int multiple);

/*Used for RSA pairs */
typedef shared_ptr<RSA> RSA_shrd_ptr;

/*Base class for cipher node of project*/
class BaseCipherUnit {
 public:
  BaseCipherUnit() = default;
  ~BaseCipherUnit() = default;

  static char* get_file_content(char* filename);
};

class RSA_Unit : public BaseCipherUnit {
  /****
  visit
  http://hayageek.com/rsa-encryption-decryption-openssl-c/
  for more info about this methods
  *****/
 public:
  RSA_Unit() = default;
  int init_public_key(unsigned char* key) __THROW;
  int init_private_key(unsigned char* key) __THROW;
  int init_keys(unsigned char* pr_key, unsigned char* pub_key) __THROW;

  int public_encrypt(unsigned char* data, int data_len,
                     unsigned char* encrypted);
  int private_decrypt(unsigned char* enc_data, int data_len,
                      unsigned char* decrypted);
  ~RSA_Unit();

 private:
  RSA* create_RSA(unsigned char* key, int is_public);
  RSA* create_RSA_with_filename(char* filename, int is_public);

  RSA_shrd_ptr public_key;
  RSA_shrd_ptr private_key;
  int padding = RSA_PKCS1_PADDING;
};

class AES_Unit : public BaseCipherUnit {
 public:
  unsigned char* generate_key(const uint16_t len = 16);
  int encrypt(unsigned char* text, int text_len, const unsigned char* key,
              unsigned char* cipher);
  int decrypt(unsigned char* cipher, int cipher_len, unsigned char* key,
              unsigned char* text);

  void set_key(const std::string& key);
  std::string get_key(void) const noexcept;

 private:
  std::string key;
};
#endif  // __CRYPTO_UNIT_H__
