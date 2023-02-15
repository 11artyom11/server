#pragma once

#include <vector>
#include <thread>
#include <queue>
#include <memory>
#include <condition_variable>
#include <atomic>
#include <functional>

/**
 * @brief Class helper for auto scopping thread-joining
 * and keeping all threads done when exiting the scope of instance of this class
 * Prevents from UB's when thread task is not finished upon exiting block scope
 */
class JoinThreads
{
    public:
        explicit JoinThreads(std::vector<std::thread>& threads_);
        ~JoinThreads();
    private:
        std::vector<std::thread>& threads;

};