#ifndef __HANDLER__
#define __HANDLER__

#include <unistd.h>
#include <semaphore.h>
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



class strless {
   public:
      bool operator() (const std::string & first, const std::string & second ) const  { 
         return first < second; 
      }
};

/*Thread container type to hold binded socket and provided threads for it*/

namespace Server
{
    class Handler;

    typedef std::unordered_map <int, std::vector<std::thread*>> thCT ;

    
    typedef std::map <std::string, int (Handler::*) (int, const std::string&), ::strless> CommMapType;
    typedef std::map <std::string, Customer::CustomerModel*, ::strless> CustomerCacheMapType;

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
            int request_customer_sign_up            (int sfd, const std::string&);
            int request_user_login                  (int sfd, const std::string&);
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