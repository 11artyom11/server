#include "../../../include/util/cyptolib/crypto_unit.h"


EVP_PKEY* BaseCipherUnit::ReadPubKey_FromFile(char* filename)
{
  FILE* fp = fopen(filename, "r");
  if (!fp) return nullptr;
  
  EVP_PKEY* key = EVP_PKEY_new();
  if (key)
  {
    EVP_PKEY_assign_RSA(key, PEM_read_RSA_PUBKEY(fp, NULL, NULL, NULL));
  }
    
  fclose(fp);
  return key;
}


EVP_PKEY* BaseCipherUnit::ReadPrivKey_FromFile(char* filename, char* passphrase)
{    
  FILE* fp = fopen(filename, "r");
  if (!fp) return nullptr;

  EVP_PKEY* key = EVP_PKEY_new();

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
EVP_PKEY* RSA_Unit::Generate_KeyPair(char* pass)
{

  char rand_buff[16];
  EVP_PKEY *pkey = NULL;
  RSA* r;

  int bits = 512;       //      512, 1024, 2048, 4096
  unsigned long exp = RSA_F4;     //      RSA_3
  OpenSSL_add_all_algorithms();

  RAND_load_file("/dev/urandom", 1024); //RAND_seed(rand_buff, 16); On linux: RAND_load_file("/dev/urandom", 1024);
  r = RSA_generate_key(bits,exp,NULL,NULL);

  if (RSA_check_key(r)!=1);;; //Check key - error out

  //Create EVP to save to file.
  pkey = EVP_PKEY_new();
  
  EVP_PKEY_set1_RSA(pkey, r);

  RSA_free(r);
  return pkey;
}

EVP_PKEY* RSA_Unit::Generate_KeyPair_Ex(char* pass)

{
    EVP_PKEY* pkey = this->Generate_KeyPair(pass);
    if (!pkey)
    {
        return nullptr;
    }
    return pkey;
}

int RSA_Unit::Generate_KeyPair_Im(char* pass,
                                    char* pub_key_name,
                                        char* priv_key_name)
{
    Debug().info("In function RSA_Unit::Generate_KeyPair_Im");
    EVP_PKEY* pkey = this->Generate_KeyPair(pass);
    
    if (!pkey)
    {
        Debug().fatal("Failed to create key pair...");
        return 1;
    }
  
    // //Save private key
    FILE* fp = fopen(priv_key_name, "w");
    
    if (!fp)
    {
        Debug().fatal("Failed to open  file for private key");
        return 1;
    }
    int res = PEM_write_PrivateKey(fp,pkey,EVP_aes_256_cbc(),NULL,0,NULL, pass);
    if (res == 0)
    {
        Debug().fatal("Failed to write private key to file");
    }
    fclose(fp);


    //Save public key
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

    fclose(fp);
    EVP_PKEY_free(pkey);

    Debug().info("Out of function RSA_Unit::Generate_KeyPair_Im");
    return 0;
}
/*
  */