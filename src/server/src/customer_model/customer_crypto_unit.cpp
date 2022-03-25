#include "../../include/customer_model/customer_crypto_unit.h"

using namespace Security;

/**
     * @brief Written to find out wether 
     * dir exists or not
     * 
     * @param dirpath 
     * @return true if exists
     * @return false otherwise
     */
bool Security::is_dir_exist (char const *dirpath)
    {        
        DIR* dir = opendir(dirpath);
        if (dir) {
            /*Dir exists*/
            closedir(dir);
            return true;
        } else if (ENOENT == errno) {
            /*Dir does not exist*/
            return false;
        } else {
            /* opendir() failed for some other reason. */
            return false;
        }
}

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
    char keystore_dir[MAX_FILE_PATH_LENGTH] = "./keystore/";
    char pub_file_name[MAX_FILE_NAME_LENGTH] = "Public.key.";
    char priv_file_name[MAX_FILE_NAME_LENGTH] = "Private.key.";
    char pub_file_path[MAX_FILE_PATH_LENGTH+MAX_FILE_NAME_LENGTH];
    char priv_file_path[MAX_FILE_PATH_LENGTH+MAX_FILE_NAME_LENGTH];


    if (is_dir_exist(""))
    {

    }

    Debug().info ("In init_server_keypair ", c_sfd);

    /*
        Example =>
                $priv_file_path
        sprintf( "     ",       
               "%s%s", 
               Relative path for keys
               "./keystore", 
               File name (same is done for private key)
               "Public.key.");
        Result =>
            ./keystore/Public.key.* is stored in $pub_file_name
    
    */
    sprintf(pub_file_path, "%s%s", keystore_dir, pub_file_name);
    sprintf(priv_file_path, "%s%s", keystore_dir, priv_file_name);

    Debug().warning (pub_file_path);
    Debug().warning (priv_file_path);

    strcat (pub_file_path, c_sfd);
    strcat (priv_file_path, c_sfd);

    rsaU.Generate_KeyPair_Im(passphrase, pub_file_path, priv_file_path);
    
    EVP_PKEY *pubkey = rsaU.ReadPubKey_FromFile(pub_file_path);
    char     *c_pubkey = rsaU.get_file_content(pub_file_path);

    EVP_PKEY *privkey = rsaU.ReadPrivKey_FromFile(priv_file_path, passphrase);
    char     *c_privkey = rsaU.get_file_content(priv_file_path);
    
    Debug().info("Retrieved pubkey \n", c_pubkey);
    Debug().info("Retrieved privkey \n", c_privkey);

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
   try
   {
        server_keypair = __other;
        return 0;       
   }
   catch(const std::exception& e)
   {
        return 1;
   }
   
}

/**
 * @brief Set retrieved client-created public RSA key
 * 
 * @param __other other RSA key instance
 * @return int 
 */
int CustomerCryptoUnit::set_client_key (const RSA_UNAR_KEY& __other)
{
    try
    {
        this->client_key = __other;
        return 0;
    }
    catch(const std::exception& e)
    {
        return 1;
    }
    
}

/**
 * @brief Return RSA_Keypair of $this model
 * 
 * @return RSA_Keypair& 
 */
RSA_Keypair& CustomerCryptoUnit::get_server_keypair (void)
{
    return this->server_keypair;
}

/**
 * @brief Return RSA_UNAR_KEY of $this model
 * 
 * @return RSA_UNAR_KEY& 
 */
RSA_UNAR_KEY& CustomerCryptoUnit::get_client_key (void)
{
    return this->client_key;
}