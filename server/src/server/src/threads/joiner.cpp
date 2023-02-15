#include "joiner.h"

/**
 * @brief Construct a new join threads::join threads object
 * 
 * @param threads_ 
 */
JoinThreads::JoinThreads(std::vector<std::thread>& threads_):
                        threads(threads_)
{}

/**
 * @brief Destroy the join threads::join threads object
 * 
 */
JoinThreads::~JoinThreads()
{
    for (auto& th : threads)
    {
        if (th.joinable())
        {
            th.join();
        }
    }
}