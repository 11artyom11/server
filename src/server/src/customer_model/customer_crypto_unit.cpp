#include <customer_crypto_unit.h>

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
 * @brief Return RSA_UNAR_KEY of $this model
 * 
 * @return RSA_UNAR_KEY& 
 */
RSA_UNAR_KEY& CustomerCryptoUnit::get_client_key (void)
{
    return this->client_key;
}