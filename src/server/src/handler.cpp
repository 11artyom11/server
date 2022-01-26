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
    sem_init (&writer_sem, 0, RWBacklog);
    sem_init (&reader_sem, 0, RWBacklog);
}

/**
 * @brief Function that will be called in function intended for
 * handling socket-writing stuff, and will be called in 
 * separate thread : semultieanously
 * 
 * @param param 
 * @return void* 
 */
void* Server::Handler::writer(void* param)
{
 
          // Lock the semaphore
    sem_wait(&writer_sem);
    writer_++;
    /*CRITICAL SECTION*/   
    Debug().info(writer_, "writer is inside\n");
 
    this_thread::sleep_for(chrono::seconds(5));
 
    Debug().info(writer_, "Writers is leaving");
    writer_--;
    Debug().info("Writers left : " , writer_);
    writer_threads[writer_].detach();
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
void* Server::Handler::reader(void* param)
{
        // Lock the semaphore
    sem_wait(&reader_sem);
    reader_++;
 

    /*CRITICAL SECTION*/

   
    Debug().info(reader_, "reader is inside\n");
    
    this_thread::sleep_for(chrono::seconds(5));
 
    Debug().info(reader_--, "Reader is leaving");
    Debug().info("Readers left : " , reader_);

    sem_post(&reader_sem);
    reader_threads[reader_].detach();
    pthread_exit(NULL);
}

/**
 * @brief join particular thread from writee thread
 * 
 * @param at_ index of joinable thread
 * @return 0 at join success 1 on join failure 
 */
int Server::Handler::join_write_thread_at(const uint32_t at_)
{
    if  (at_ >= MAX_WRITE_THREAD_COUNT) return EXIT_FAILURE;

    if (! writer_threads[at_].joinable()) return EXIT_FAILURE;
    writer_threads[at_].join();
    return EXIT_SUCCESS;
}

/**
 * @brief join particular thread from reader thread
 * 
 * @param at_ index of joinable thread
 * @return 0 at join success 1 on join failure 
 */
int Server::Handler::join_read_thread_at(const uint32_t at_)
{
    if  (at_ >= MAX_READ_THREAD_COUNT) return EXIT_FAILURE;

   if (! reader_threads[at_].joinable()) return EXIT_FAILURE;
    reader_threads[at_].join();
    return EXIT_SUCCESS; 
}

/**
 * @brief Join all initialized threads commited for writing process
 * 
 * @return 0 on absolute success 1 on at least one join-failure 
 */
int Server::Handler::join_all_writer_threads(void)
{
    for (auto at_ = 0; at_ < writer_; ++at_)
    {
        if (join_write_thread_at(at_)) return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/**
 * @brief Join all initialized threads commited for reading process
 * 
 * @return 0 on absolute success 1 on at least one join-failure 
 */
int Server::Handler::join_all_reader_thread(void)
{
    for (auto at_ = 0; at_ < reader_; ++at_)
    {
        if (join_read_thread_at(at_)) return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/**
 * @brief provide new socket a writ - support with separate thread
 * 
 * @param new_write_socket 
 * @return 0 on success 1 on opposite result 
 */
int Server::Handler::provide_write_thread(int new_write_socket)
{
    Debug().fatal("BEFORE THREAD CREATING");
    writer_threads[writer_] = thread(&Server::Handler::writer,this, &new_write_socket);
        Debug().fatal("AFTER THREAD CREATING");

    bool success = writer_threads[writer_].joinable();
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
        Debug().fatal("BEFORE THREAD CREATING");

        reader_threads[reader_] = thread (&Server::Handler::reader,this, &new_read_socket);
        Debug().fatal("BEFORE THREAD CREATING");

    bool success = reader_threads[reader_].joinable();
    if (success)
    {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}