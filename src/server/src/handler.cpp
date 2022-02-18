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
    commap[WRITE_REQ] = &Server::Handler::provide_write_thread;
    commap[READ_REQ]  = &Server::Handler::provide_read_thread;
    commap[EXIT_MESSAGE] = &Server::Handler::terminate_socket;
    commap[SIGN_NEW_CUSTOMER_MESSAGE] = &Server::Handler::sign_new_customer;
}

/**
 * @brief Function that will be called in function intended for
 * handling socket-writing stuff, and will be called in 
 * separate thread : semultieanously
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

int Server::Handler::sign_new_customer(int sfd)
{
    Debug().info("Called Server::Handler::sign_new_customer( ", sfd, ")");
    this->recent_customers[sfd] = new Customer::CustomerModel(sfd);
    this->recent_customers[sfd]->get_crypto_unit()->init_server_keypair((char*)RSA_DEFAULT_PASSPHRASE);

    return 0;
}



/**
 * @brief provide new socket a writ - support with separate thread
 * 
 * @param new_write_socket 
 * @return 0 on success 1 on opposite result 
 */
int Server::Handler::provide_write_thread(int new_write_socket)
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
int Server::Handler::provide_read_thread(int new_read_socket)
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
int Server::Handler::terminate_socket( int sfd)
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
 * @brief 
 * 
 * @param command 
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