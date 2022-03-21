#include "./../../../lib/include/helpers/debug_helper/debug_helper.h"
#include "../include/handler.h"

using namespace std;

/**
 * @brief Construct a new Server:: Handler:: Handler object
 * 
 * @param RWBeacklog represents number of allowed thread count
 * to use reader & writer function at the same time
 */
Server::Handler::Handler(int RWBacklog)
{
    Debug().info("Called handel ctor");
    sem_init (&writer_sem, 0, RWBacklog);
    sem_init (&reader_sem, 0, RWBacklog);
    commap_init();
}

/**
 * @brief Init map which contains command as string (key) and function pointer 
as value , which will be implicitly called when according command was called
    @note this function values must be member functions or implicitly been derived from
        class type Server::Handler
        ptr type : 
    int (Server::Handler::*)(int)
 */
void Server::Handler::commap_init (void)
{
    Debug().info("Cted commap");

    commap[LOG_IN_REQUEST]  = &Server::Handler::response_to_user_login;
    commap[SIGN_UP_REQUEST]  = &Server::Handler::response_to_customer_sign_up;
    commap[LOG_IN_COMMAND]  = &Server::Handler::log_in_to_system;
    commap[SIGN_UP_COMMAND] = &Server::Handler::sign_new_customer;
    commap[WRITE_COMMAND]   = &Server::Handler::provide_write_thread;
    commap[READ_COMMAND]    = &Server::Handler::provide_read_thread;
    commap[EXIT_COMMAND]    = &Server::Handler::terminate_socket;

}

/**
 * @brief Function that will be called in function intended for
 * handling socket-writing stuff, and will be called in 
 * separate thread : simultieanously
 * 
 * @param param 
 * @return void* 
 */
void* Server::Handler::writer(int sfd, uint32_t tid)
{
          // Lock the semaphore
    sem_wait(&writer_sem);
    writer_++;

    /*CRITICAL SECTION*/ 

    Debug().info(writer_, "writer is inside\n");
    this_thread::sleep_for(chrono::seconds(1));
    Debug().info("Writer", writer_--, " is leaving");
    Debug().info("Writers left : " , writer_);
    writer_threads[sfd].at(tid)->detach();

    /*CRITICAL SECTION*/

    sem_post(&writer_sem);    
    pthread_exit(NULL);
}

/**
 * @brief Function that will be called in function intended for
 * handling socket-reading stuff, and will be called in 
 * separate thread : semultieanously
 * 
 * @param param 
 * @return void* 
 */
void* Server::Handler::reader(int sfd , uint32_t tid)
{
    // Lock the semaphore
    sem_wait(&reader_sem);
    reader_++;
 

    /*CRITICAL SECTION*/
   
    Debug().info(reader_, "reader is inside\n");
    
    this_thread::sleep_for(chrono::seconds(1));
 
    Debug().info("Reader", reader_--, " is leaving");
    Debug().info("Readers left : " , reader_);

    sem_post(&reader_sem);
    /*CRITICAL SECTION*/

    reader_threads[sfd].at(tid)->detach();
    pthread_exit(NULL);
}

/**
 * @brief String randomizer
 * 
 * @param len string length to be returned
 * @return std::string 
 */
std::string Server::random_str(int len)
{
    std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

    std::random_device rd;
    std::mt19937 generator(rd());

    std::shuffle(str.begin(), str.end(), generator);

    return str.substr(0, len); // assumes 32 < number of characters in str
}


/* HANDLERS */

/**
  * @brief Send response to client  in order to give to the client
 * an information about log_in (reject or accept request)
 * 
 * @param sfd connection descriptor
 * @return 0 on success 1 otherwise
 */
int Server::Handler::response_to_customer_sign_up(int sfd, const std::string&)
{
    Debug().warning("Called Server::Handler::request_customer_sign_up STILL NOT IMPLEMENTED");
    return 0;
}

/**
 * @brief Send response to client  in order to give to the client
 * an information about sign_up (reject or accept request)
 * 
 * @param sfd connection descriptor
 * @return 0 on success 1 otherwise
 */
int Server::Handler::response_to_user_login(int sfd, const std::string&)
{
    Debug().warning("Called Server::Handler::request_user_login STILL NOT IMPLEMENTED");
    return 0;
}

/**
 * @brief Send $SIGN_UP_COMMAND command with corresponding credentials to server
 * in order to sign up as new customer
 * 
 * @param sfd connection descriptor
 * @return 0 on success 1 otherwise 
 */
int Server::Handler::sign_new_customer(int sfd, const std::string&)
{
    Debug().info("Called Server::Handler::sign_new_customer( ", sfd, ")");
    std::string new_unique_token = Server::random_str();

    this->recent_customers[new_unique_token] = new Customer::CustomerModel(sfd, new_unique_token);
    this->recent_customers[new_unique_token]->get_crypto_unit()->init_server_keypair((char*)RSA_DEFAULT_PASSPHRASE);

    return 0;
}

/**
 * @brief Send $LOG_IN_COMMAND command in with corresponding credentials
 * in order to log in as existing user 
 * 
 * @param sfd 
 * @return int 
 */
int Server::Handler::log_in_to_system(int sfd, const std::string&)
{
    /*Request to DB in order to make some calculations , still have 
    nothing to do
    Last edit : Mar 17 2022
    */
   return 0;
}


/**
 * @brief provide new socket a writ - support with separate thread
 * 
 * @param new_write_socket 
 * @return 0 on success 1 on opposite result 
 */
int Server::Handler::provide_write_thread(int new_write_socket, const std::string&)
{
    Debug().info("WRITE THREAD");
    /*Index of newly created thread to be passing to writer function*/
    int tid = writer_threads[new_write_socket].size();
    
    /*Create new thread and push it into end of vector of threads of 
        corresponding sfd*/
    std::thread* new_thread = new std::thread(&Server::Handler::writer, this, new_write_socket, tid);
    writer_threads[new_write_socket].push_back(new_thread);
    bool success = writer_threads[new_write_socket].at(tid)->joinable();
    alive_writer_sockets.push_back(new_write_socket);

       /*If succeeded to create a new thread
     for new socket increment writers count & return success code
      else return failure code */
    if (success)
    {
        return EXIT_SUCCESS;
    } 
    return EXIT_FAILURE;
}


/**
 * @brief provide new socket a read - support with separate thread
 * 
 * @param new_read_socket 
 * @return 0 on success 1 on opposite result 
 */
int Server::Handler::provide_read_thread(int new_read_socket, const std::string&)
{
    /*Index of newly created thread to be passing to reader function*/
    int tid = reader_threads[new_read_socket].size();
    
    /*Create new thread and push it into end of vector of threads of 
        corresponding sfd*/
    std::thread* new_thread = new std::thread(&Server::Handler::reader, this, new_read_socket, tid);
    reader_threads[new_read_socket].push_back(new_thread);
    alive_reader_sockets.push_back(new_read_socket);
    bool success = reader_threads[new_read_socket].at(tid)->joinable();

    if (success)
    {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

/**
 * @brief close connected socket passed as parameter
 * 
 * @param sfd socket to close
 * @return close success code 
 */
int Server::Handler::terminate_socket( int sfd, const std::string&)
{
    Debug().info("Connection terminated");
    /*
    clean all garbage which will be left after socket 
    termination
    */
    // cleanup_socket_garbage(sfd);
    if (close (sfd) == 0)
    {
        return TERMINATE_CODE_SUCCESS;
    }
    return TERMINATE_CODE_FAILURE;
}

/**
 * @brief Clean threads if such exist in writer / reader containers
 * 
 * @param sfd to clean after
 * @return int success code
 */
int Server::Handler::cleanup_socket_garbage (int sfd)
{
    /*Clean all thread provided for writing into system for given socket*/
    if (cleanup_writer_thread_for_socket(sfd) == 0)
    {
        /*Delete socket key-value binding from writer storing container*/
        /*as long as cleanup was succeeded*/
        writer_threads.erase (sfd);
    }

    /*Clean all thread provided for reading into system for given socket*/
    if (cleanup_reader_thread_for_socket(sfd) == 0)
    {
        /*Delete socket key-value binding from reader storing container*/
        /*as long as cleanup was succeeded*/
        reader_threads.erase (sfd);
    }

}

/**
 * @brief clean reader threads provided for given socket
 * 
 * @param sfd socket which reader trheads will be killed
 * @return 0 for success 1 on failure
 */
int Server::Handler::cleanup_reader_thread_for_socket (int sfd)
{
    auto provided_read_threads = reader_threads[sfd];
    std::for_each(provided_read_threads.begin(), provided_read_threads.end(), delete_ptr());
    return (bool)reader_threads[sfd].size();
}

/**
 * @brief clean writer threads provided for given socket
 * 
 * @param sfd socket which reader trheads will be killed
 * @return 0 for success 1 on failure
 */
int Server::Handler::cleanup_writer_thread_for_socket (int sfd)
{
    auto provided_write_threads = writer_threads[sfd];
    std::for_each(provided_write_threads.begin(), provided_write_threads.end(), delete_ptr());
    return (bool)writer_threads[sfd].size();
}

/**
 * @brief Return according handler-function pointer based on passed
 * command name 
 * these bindings are stored in associative containers
 * 
 * @param command string indroduction of command 
 * @return decltype (&Server::Handler::provide_write_thread) 
 */
decltype (&Server::Handler::provide_write_thread) 
Server::Handler::get_command (std::string command)
{
    try
    {
        Debug().info("SIZE : ", commap.size());
        return commap.at(command);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return nullptr;
    }
}

/**
 * @brief Request DB or local tmp cache in order to find according 
 * user by particular credentials
 * 
 * @param unique_token  Particular unique credential
 * @return int 
 */
int Server::Handler::find_in_customer_cache(const std::string& unique_token)
{
    auto customer = recent_customers[unique_token];
    if (customer == nullptr) return -1;
    else return customer->get_sfd();
}

/**
 * @brief Destroy the Server:: Handler:: Handler object
 * 
 */
Server::Handler::~Handler()
{
    Debug().info("HANDLER DESTRUCTED");
    for (const auto&  sfd : alive_writer_sockets)
    {
        cleanup_socket_garbage(sfd);
    }
    writer_threads.clear();
    reader_threads.clear();
    alive_reader_sockets.clear();
    alive_writer_sockets.clear();
}