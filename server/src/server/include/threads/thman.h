#pragma once

#include <vector>
#include <thread>
#include <queue>
#include <memory>
#include <condition_variable>
#include <atomic>
#include <functional>

#include "thread_safe_queue.h"
#include "joiner.h"

/**
 * @brief Class for automatically managing tasks and 
 * distribute them between maximum of hw - supported number
 * of threads.
 * 
 */
class ThreadPool
{
    public:
        ThreadPool();
        ~ThreadPool();

        template <typename FuncType> void submit(FuncType f);

    private:
        std::atomic<bool> done;
        ThreadSafeQueue<std::function<void()>> work_queue;
        std::vector<std::thread> threads;
        JoinThreads joiner;
        void worker_thread();
};


/**
 * @brief Submit new task for threads to do
 * 
 * @tparam FuncType 
 * @param f 
 */
template <typename FuncType>
void ThreadPool::submit(FuncType f)
{
    work_queue.push(std::function<void()>(f));
}




