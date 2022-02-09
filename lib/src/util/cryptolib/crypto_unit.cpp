#include "../../../include/util/cyptolib/crypto_unit.h"


EVP_PKEY* BaseCipherUnit::ReadPubKey_FromFile(char* filename)
{
  FILE* fp = fopen(filename, "r");
  if (!fp) return nullptr;
  
  EVP_PKEY* key = EVP_PKEY_new();
  if (key)
  {
    EVP_PKEY_assign_RSA(key, PEM_read_RSAPublicKey(fp, NULL, NULL, NULL));
  }

  fclose(fp);
  return key;
}


EVP_PKEY* BaseCipherUnit::ReadPrivKey_FromFile(char* filename)
{
  FILE* fp = fopen(filename, "r");
  if (!fp) return nullptr;

  EVP_PKEY* key = EVP_PKEY_new();
  if (key)
  {
    EVP_PKEY_assign_RSA(key, PEM_read_RSAPrivateKey(fp, NULL, NULL, NULL));
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
RSA* RSA_Unit::Generate_KeyPair(char* pass)
{
  char rand_buff[16];
  EVP_PKEY *pkey = NULL;
  RSA* r;

  int bits = 512;       //      512, 1024, 2048, 4096
  unsigned long exp = RSA_F4;     //      RSA_3
  OpenSSL_add_all_algorithms();

  RAND_seed(rand_buff, 16); //On linux: RAND_load_file("/dev/urandom", 1024);
  r = RSA_generate_key(bits,exp,NULL,NULL);

  if (RSA_check_key(r)!=1);;; //Check key - error out

  //Create EVP to save to file.
  pkey = EVP_PKEY_new();
  EVP_PKEY_assign_RSA(pkey, r);

  //Save private key
  FILE* fp = fopen("private.key", "w");
  PEM_write_PrivateKey(fp,pkey,EVP_aes_256_cbc(),NULL,0,NULL, pass);
  fclose(fp);

  //Save public key
  fp = fopen("public.key", "w");
  PEM_write_PUBKEY(fp, pkey);
  fclose(fp);

  return r;
}

