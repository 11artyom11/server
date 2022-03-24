/**
 * @file handler.h
 * @author Artyom Grigorian (grigorianartyom1@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-20
 * @section DESCRIPTION
 * This Handler class is made to develop initial distibruting
 * of incoming commands from remote nodes (clients)
 * and to provide DB and Server Core resources for requesting connections 
 * Is Defined in Server namespace
 * 
 * @section Last Changes 23-03-2022 Artyom Grigorian\
 * Changed recent customer's naked pointer model
 * into smart pointers
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __HANDLER__
#define __HANDLER__

#include <unistd.h>
#include <semaphore.h>
#include <memory>
#include <thread>
#include <unordered_map>
#include <map>
#include <vector>
#include <random>
#include <string>
#include <algorithm>
#include "../include/customer_model/customer.h"

// Helper functor to ease cleanup of container
struct delete_ptr { 
    template <typename P>
    void operator () (P p) {
        delete p;
    }
};


/**
 * @brief class to define string comparison in vector
 * 
 */
class strless {
   public:
      bool operator() (const std::string & first, const std::string & second ) const  { 
         return first < second; 
      }
};


namespace Server
{
    class Handler;

    template <typename T>
    using shared_ptr = std::shared_ptr<T>;

    /*socket file descriptor and thhread vector container (MAP)*/
    typedef std::unordered_map <int, std::vector<std::thread*>> thCT ;   
    
    /*Binding which help to add new handler functions genreically*/
    typedef std::map <std::string, int (Handler::*) (int, const std::string&), ::strless> CommMapType;
    
    /*Shared ptr type for Customer Model*/
    typedef shared_ptr<Customer::CustomerModel> CustomerModel_shrd_ptr;

    /*Recent Customer cache type stores in trivial way*/
    typedef std::map <std::string, CustomerModel_shrd_ptr, ::strless> CustomerCacheMapType;

/*Function for random string generating*/
std::string random_str(int len = 40);
    class Handler
    {
        public:
            Handler (int RWBacklog = 1);
            ~Handler ();
            void commap_init (void);

            void* writer (int sfd , uint32_t tid);
            void* reader (int sfd , uint32_t tid);
            

            /*HANDLER FUNCTIONS*/
            /* these functions are required to process all retrieved sanctioned data */
            int response_to_customer_sign_up        (int sfd, const std::string&);
            int response_to_user_login              (int sfd, const std::string&);
            int sign_new_customer                   (int sfd, const std::string&);
            int log_in_to_system                    (int sfd, const std::string&);
            int provide_write_thread                (int sfd, const std::string&);
            int provide_read_thread                 (int sfd, const std::string&);
            int terminate_socket                    (int sfd, const std::string&);
            
            /* CLEANERS */
            int cleanup_socket_garbage              (int sfd);
            int cleanup_reader_thread_for_socket    (int sfd);
            int cleanup_writer_thread_for_socket    (int sfd);

            decltype(&Server::Handler::provide_write_thread) get_command  ( std::string command);
            int find_in_customer_cache(const std::string& unique_token);
        private:
            sem_t writer_sem;
            sem_t reader_sem;

            inline static int reader_ = 0;
            inline static int writer_ = 0;


            thCT writer_threads;
            thCT reader_threads;
            
            /*
            Containers to store socket descriptors 
            which are alive and can hold connection
            */
            std::vector <int> alive_writer_sockets;
            std::vector <int> alive_reader_sockets;

            CommMapType commap;

            /*Cache which holds recent customers*/
            CustomerCacheMapType recent_customers;

    };
};
    

#endif //__HANDLER__