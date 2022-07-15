/**
 * @file communication_unit.h
 * @author Artyom Grigorian (grigorianartyom1@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-20
 * @section DESCRIPTION
 * This class is made to provide communication bridge between 
 * client and server core
 * Is Used at both sides.
 * Is defined in Net namespace
 * 
 * @section Last Changes 21-04-2022 Artyom Grigorian
 *
 * Improved include directories
 *  
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __COMM_UNIT_H__
#define __COMM_UNIT_H__
#include "connection_handler.h"

#include "message_model.h"
#include "message_resolver.h"
#include "io_unit.h"

#include <future>
#include <memory>
#include <thread>
#include <semaphore.h>

constexpr auto max_read_th_count = 3;
constexpr auto max_write_th_count = 3;



namespace Net
{
    template <typename T>
    using unique_ptr = std::unique_ptr<T>;

    typedef shared_ptr<iounit::IOModel> \
                 IOModel_shrd_ptr;

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

            IOModel_shrd_ptr get_io_model (void) const;
        private:
            IOModel_shrd_ptr m_io_model;

            /*Semaphores to keep maximum N threads forked to read & write*/
            sem_t read_lock;
            sem_t write_lock;

            /*Maximum count of forked read and write threads*/
            uint32_t max_read_thread_count;
            uint32_t max_write_thread_count;
    };
};  
#endif
