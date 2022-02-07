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
void* Server::Handler::writer(int sfd, uint32_t tid)
{
 
    
          // Lock the semaphore
    sem_wait(&writer_sem);
    writer_++;

    /*CRITICAL SECTION*/ 

    Debug().info(writer_, "writer is inside\n");
    this_thread::sleep_for(chrono::seconds(5));
    Debug().info("Writer", writer_, " is leaving");
    writer_--;
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
    Debug().warning("HERE 1.5");
    // Lock the semaphore
    sem_wait(&reader_sem);
    reader_++;
 

    /*CRITICAL SECTION*/
   
    Debug().info(reader_, "reader is inside\n");
    
    this_thread::sleep_for(chrono::seconds(5));
 
    Debug().info("Reader", reader_--, " is leaving");
    Debug().info("Readers left : " , reader_);

    sem_post(&reader_sem);
    /*CRITICAL SECTION*/

    reader_threads[sfd].at(tid)->detach();
    pthread_exit(NULL);
}

/**
 * @brief provide new socket a writ - support with separate thread
 * 
 * @param new_write_socket 
 * @return 0 on success 1 on opposite result 
 */
int Server::Handler::provide_write_thread(int new_write_socket)
{
    /*Index of newly created thread to be passing to writer function*/
    int tid = writer_threads[new_write_socket].size();
    
    /*Create new thread and push it into end of vector of threads of 
        corresponding sfd*/
     std::thread* new_thread = new std::thread(&Server::Handler::writer, this, new_write_socket, tid);
    writer_threads[new_write_socket].push_back(new_thread);
   Debug().warning("Before");
    bool success = writer_threads[new_write_socket].at(tid)->joinable();
   Debug().warning("After");
   
    
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
    bool success = reader_threads[new_read_socket].at(tid)->joinable();
    if (success)
    {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}