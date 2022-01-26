#include "./../../../lib/include/helpers/debug_helper/debug_helper.h"
#include "../include/handler.h"

using namespace std;

/**
 * @brief Construct a new Server:: Handler:: Handler object
 * 
 * @param RWBeacklog represents number of allowed thread count
 * to use reader & writer function at the same time
 */
Server::Handler::Handler(int RWBeacklog)
{
    sem_init (&writer_sem, 0, RWBeacklog);
    sem_init (&reader_sem, 0, RWBeacklog);
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
    printf("\nWriter is trying to enter");
 
    // Lock the semaphore
    sem_wait(&writer_sem);
 
    printf("\nWriter has entered");
 
    // Unlock the semaphore
    sem_post(&writer_sem);
 
    printf("\nWriter is leaving");
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
 
    if (reader_ == 1)
        sem_wait(&writer_sem);
 
    // Unlock the semaphore
    sem_post(&reader_sem);
 
    printf("\n%d reader is inside",
           reader_);
 
    this_thread::sleep_for(chrono::seconds(5));
 
    // Lock the semaphore
    sem_wait(&reader_sem);
    reader_--;
 
    if (reader_ == 0) {
        sem_post(&writer_sem);
    }
 
    // Lock the semaphore
    sem_post(&reader_sem);
 
    printf("\n%d Reader is leaving",
           reader_ + 1);
    pthread_exit(NULL);
}


int Server::Handler::provide_write_thread(int new_write_socket)
{

    writer_threads[writer_count] = thread(&Server::Handler::writer,this, &new_write_socket);
    bool success = writer_threads[writer_count].joinable();
    /*If succeeded to create a new thread
     for new socket increment writers count & return success code
      else return failure code */
    if (success)
    {
        ++writer_count;
        return EXIT_SUCCESS;
    } 
    return EXIT_FAILURE;
}

int Server::Handler::provide_read_thread(int new_read_socket)
{
    reader_threads[reader_count] = thread (&Server::Handler::reader,this, &new_read_socket);
    bool success = reader_threads[reader_count].joinable();
    if (success)
    {
        ++reader_count;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}