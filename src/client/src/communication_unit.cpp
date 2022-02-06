#include "../include/communication_unit.h"

using namespace Net;

/**
 * @brief Construct a new Basic Communication Model:: Basic Communication Model object
 * 
 */
BasicCommunicationModel::BasicCommunicationModel() :
    BasicCommunicationModel(max_read_th_count, 
                                max_write_th_count)
{

}

/**
 * @brief Construct a new Basic Communication Model:: Basic Communication Model object
 * 
 * @param max_read_thread_count Maximum read thread count that can be forked at once
 * @param max_write_thread_count  Maximum write thread count that can be forked at once
 */
BasicCommunicationModel::BasicCommunicationModel(uint32_t _max_read_thread_count,
                                                    uint32_t _max_write_thread_count)
{
    this->m_io_model = new iounit::IOModel();
    this->max_read_thread_count = _max_read_thread_count;
    this->max_write_thread_count = _max_write_thread_count;
    sem_init (&read_lock,0, _max_read_thread_count);
    sem_init (&write_lock,0, _max_write_thread_count);
}

/**
 * @brief Destroy the Basic Communication Model:: Basic Communication Model object
 * 
 */
BasicCommunicationModel::~BasicCommunicationModel()
{
    delete this->m_io_model;
}

/**
 * @brief Starting N count of forked threads which are async-ly 
 * reading from socket and sent to function of output
 * 
 * @param sockfd 
 * @return void* 
 */

//[*need to think over*] maybe add std::ostream to pass to io->read function
void BasicCommunicationModel::start_read_async(int sockfd)
{
    Debug().info("Called BasicCommunicationModel::start_read_async(..)");
    /*Lambda which is called to frok another thread in order to 
        support async read model and not to mess with write model*/
    auto wait_to_read_and_start_read_q = [this, &sockfd]()
    {
        for (;;) 
        {
        /*While conenction has not been 
            terminated keep reading from sockfd*/
            /*This infinite loop can hold maximum $max_read_thread_count
            connections*/
            sem_wait(&read_lock);
            
            char buff[1024];
            int n;
            bzero(buff, sizeof(buff));
            
            int read_result = read(sockfd, buff, sizeof(buff));
            if (read_result == 0)
            {
                Debug().fatal("Host is no longer available. Terminating...");
                exit(0);
            }
            Debug().info("READ RESULT : ", read_result);
            /*Start new thread to print retrieved buffer*/
            m_io_model->read_q(buff);
            sem_post(&read_lock);
        }
    };
    
        /*Async-ly start read lambda (see :43) */
    std::async(std::launch::async, wait_to_read_and_start_read_q);          
    
    Debug().info("Ended BasicCommunicationModel::start_read_async(..)");
}

/**
 * @brief Function to support async writing function 
 * don't need to support multi stream work yet. Maybe later feature 
 * will be added.
 * 
 * @param sockfd 
 * @return void* 
 */
void BasicCommunicationModel::start_write_async(int sockfd, 
                                                    std::istream&)
{          
    std::string buf_s;
    while (getline(std::cin, buf_s) )
    {
        write(sockfd, buf_s.c_str(), sizeof(buf_s.c_str()));
        buf_s.clear();
    }
}



