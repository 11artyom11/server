#include "../../include/customer_model/customer_crypto_unit.h"

using namespace Security;

CustomerCryptoUnit::CustomerCryptoUnit(int sfd)
{

    Debug().info("Constructed CustomerCryptoUnit object : ", sfd);   
    /*Means that sfd can hold up to 16digit sfd cahr array model*/
    
    c_sfd = new char [(int)(ceil(log10(sfd))+1)*sizeof(char)];
    Debug().info("customer.cpp 12");
    sprintf (c_sfd, "%d", sfd);
    Debug().info("STR : ", c_sfd);
}

CustomerCryptoUnit::~CustomerCryptoUnit()
{
    // delete c_sfd;
    Debug().info("Destroyed CustomerCryptoUnit::~CustomerCryptoUnit()");
}

/**
 * @brief generate rsa keypair (considered as server side) and save in in
 * pair in objet member field
 * 
 * @param passphrase passwor for private key
 * @return 0 on success other value on failure 
 */
int CustomerCryptoUnit::init_server_keypair (char* passphrase)
{
    Debug().info("CustomerCryptoUnit::init_server_keypair (char* passphrase)");
    RSA_Unit rsaU;
    /*grab character under ascii firecode of sfd which is also unique*/
    /*if sfd is not given do generating in common buffer Public.key*/
    char pub_file_name[1024] = "keystore/Public.key.";
    Debug().info ("In init_server_keypair ", c_sfd);
    strcat (pub_file_name, c_sfd);

    char priv_file_name[1024] = "keystore/Private.key.";
    strcat (priv_file_name, c_sfd);

    rsaU.Generate_KeyPair_Im(passphrase, pub_file_name, priv_file_name);
    
    EVP_PKEY *pubkey = rsaU.ReadPubKey_FromFile(pub_file_name);
    char     *c_pubkey = rsaU.get_file_content(pub_file_name);

    EVP_PKEY *privkey = rsaU.ReadPrivKey_FromFile(priv_file_name, passphrase);
    char     *c_privkey = rsaU.get_file_content(priv_file_name);
    
    Debug().info("Retrieved pubkey \n", c_pubkey);
    Debug().info("Rettrieved privkey \n", c_privkey);

    this->server_keypair = {RSA_UNAR_KEY{pubkey, c_pubkey}, 
                            RSA_UNAR_KEY{privkey, c_privkey}};
    
    Debug().info("Out of function init_server_keypair");
    return (int)!(sizeof (c_pubkey) & sizeof (c_privkey));
}

/**
 * @brief Set already existing RSA_Keypair (typedef) to model
 * 
 * @param __other init keypair from other pair instance
 * @return int 
 */
int CustomerCryptoUnit::set_server_keypair (const RSA_Keypair& __other)
{

}

/**
 * @brief Set retrieved client-created public RSA key
 * 
 * @param __other other RSA key instance
 * @return int 
 */
int CustomerCryptoUnit::set_client_key (const RSA_UNAR_KEY& __other)
{

}

/**
 * @brief Return RSA_Keypair of $this model
 * 
 * @return RSA_Keypair& 
 */
RSA_Keypair& CustomerCryptoUnit::get_server_keypair (void)
{

}

/**
 * @brief Return RSA_UNAR_KEY of $this model
 * 
 * @return RSA_UNAR_KEY& 
 */
RSA_UNAR_KEY& CustomerCryptoUnit::get_client_key (void)
{

}