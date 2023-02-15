#pragma once

#include "thman.h"

ThreadPool::ThreadPool() :
            done (false),
                joiner(threads)
{
    unsigned int hw_count = std::thread::hardware_concurrency();
    try
    {
        for (size_t i = 0; i < hw_count; ++i){
            threads.push_back(std::thread(&ThreadPool::worker_thread, this));
        }
    }
    catch(...)
    {
        done = true;
        throw;
    }
}

void ThreadPool::worker_thread()
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

ThreadPool::~ThreadPool()
{
    done = true;
}