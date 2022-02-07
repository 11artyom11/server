#ifndef __COMM_UNIT_H__
#define __COMM_UNIT_H__
#include "connection_handler.h"
#include "io_unit.h"
#include <future>
#include <thread>
#include <semaphore.h>

constexpr auto max_read_th_count = 3;
constexpr auto max_write_th_count = 3;


namespace Net
{
    class BasicCommunicationModel
    {   
        public:
            BasicCommunicationModel();
            BasicCommunicationModel(uint32_t max_read_thread_count,
                                        uint32_t max_write_thread_count);
            ~BasicCommunicationModel();

            /*functions for async reading and writing*/
            void start_read_async(int sockfd);
            void start_write_async(int sockfd, std::istream& is);
        private:
            iounit::IOModel* m_io_model;

            /*Semaphores to keep maximum N threads forked to read & write*/
            sem_t read_lock;
            sem_t write_lock;

            /*Maximum count of forked read and write threads*/
            uint32_t max_read_thread_count;
            uint32_t max_write_thread_count;

            

    };
};  
#endif
