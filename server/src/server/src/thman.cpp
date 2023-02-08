#include "thman.h"

join_threads::join_threads(std::vector<std::thread>& threads_):
                        threads(threads_)
{}

join_threads::~join_threads()
{
    for (auto& th : threads)
    {
        if (th.joinable())
        {
            th.join();
        }
    }
}

thread_pool::thread_pool() :
            done (false),
                joiner(threads)
{
    unsigned int hw_count = std::thread::hardware_concurrency();
    try
    {
        for (size_t i = 0; i < hw_count; ++i){
            threads.push_back(std::thread(&thread_pool::worker_thread, this));
        }
    }
    catch(...)
    {
        done = true;
        throw;
    }
}

void thread_pool::worker_thread()
{
    while (!done)
    {
        std::function<void()> task;
        if (work_queue.try_pop(task)){
            task();
        } else {
            std::this_thread::yield;
        }
    } 
}

thread_pool::~thread_pool()
{
    done = true;
}