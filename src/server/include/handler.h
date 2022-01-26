#ifndef __HANDLER__
#define __HANDLER__

#include <semaphore.h>
#include <thread>


namespace Server
{
    class Handler
    {
        public:
            Handler (int RWBacklog = 1);
            ~Handler () = default;

            void* writer (void* param);
            void* reader (void* param);
        
        protected:
            int provide_write_thread (int new_write_socket);
            int provide_read_thread  (int new_read_socket);

        private:
            sem_t writer_sem;
            sem_t reader_sem;
            inline static int reader_ = 0;

            std::thread writer_threads[MAX_WRITE_THREAD_COUNT];
            std::thread reader_threads[MAX_READ_THREAD_COUNT];
            inline static uint32_t writer_count = 0;
            inline static uint32_t reader_count = 0;

    };
};
    

#endif //__HANDLER__