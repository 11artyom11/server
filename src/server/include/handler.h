#ifndef __HANDLER__
#define __HANDLER__

#include <semaphore.h>
#include <thread>
#include <unordered_map>
#include <vector>


namespace Server
{
    class Handler
    {
        public:
            Handler (int RWBacklog = 1);
            ~Handler () = default;

            void* writer (int sfd , uint32_t tid);
            void* reader (int sfd , uint32_t tid);

            int provide_write_thread (int new_write_socket);
            int provide_read_thread  (int new_read_socket);

        private:
            sem_t writer_sem;
            sem_t reader_sem;

            inline static int reader_ = 0;
            inline static int writer_ = 0;


            std::unordered_map <int, std::vector<std::thread*>> writer_threads;
            std::unordered_map <int,std::vector<std::thread*>> reader_threads;
           

    };
};
    

#endif //__HANDLER__