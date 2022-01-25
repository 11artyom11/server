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

        private:
            sem_t writer_sem;
            sem_t reader_sem;
            inline static int readercount = 0;

    };
};
    

#endif //__HANDLER__