#pragma once

#include <vector>
#include <thread>
#include <queue>
#include <memory>
#include <condition_variable>
#include <atomic>
#include <functional>

/**
 * @brief STL queue wrapper = thread safe queue to do standard operations atomically and
 * relativaely safe compared to stl queue
 * 
 * @tparam T 
 */
template <typename T>
class ThreadSafeQueue
{
    public:
        ThreadSafeQueue() = default;
        ThreadSafeQueue(ThreadSafeQueue const& other);
        void push(T new_value);
        void wait_and_pop(T& value);
        bool try_pop(T& value);
        bool empty () const;

    private:
        mutable std::mutex mut;
        std::queue<T> data_queue;
        std::condition_variable data_cond;
};


/**
 * @brief Construct a new thread safe queue<T>::thread safe queue object
 * 
 * @tparam T 
 * @param other 
 */
template <typename T>
ThreadSafeQueue<T>::ThreadSafeQueue(const ThreadSafeQueue<T> & other)
{
    std::lock_guard<std::mutex> scope_lock (other.mut);
    data_queue = other.data_queue;
}

/**
 * @brief Atomically push new queue member to the end of list 
 * 
 * @tparam T 
 * @param new_value 
 */
template <typename T>
void ThreadSafeQueue<T>::push(T new_value)
{
    std::lock_guard<std::mutex> scope_lock(mut);
    data_queue.push(new_value);
    data_cond.notify_one();
}

/**
 * @brief Wait for mutex to unlock and pop last item from queue
 * 
 * @tparam T 
 * @param value 
 */
template <typename T>
void ThreadSafeQueue<T>::wait_and_pop(T& value)
{
    std::unique_lock<std::mutex> scope_lock(mut);
    data_cond.wait(scope_lock, [this]{return !data_queue.empty();});
    value = data_queue.front();
    data_queue.pop();
}

/**
 * @brief Atomically pop last item from queue if one exists
 * 
 * @tparam T 
 * @param value 
 * @return true if succeed
 * @return false if failed
 */
template <typename T>
bool ThreadSafeQueue<T>::try_pop(T& value)
{
    std::lock_guard<std::mutex> scope_lock (mut);
    if (data_queue.empty()){
        return false;
    } 
    value = data_queue.front();
    data_queue.pop();
    return true;
}

/**
 * @brief ATOMICALLY check emptiness of thread safe queue 
 * 
 * @tparam T 
 * @return true if empty 
 * @return false if NOT empty
 */
template <typename T>
bool ThreadSafeQueue<T>::empty() const
{
    std::lock_guard<std::mutex> scope_lock(mut);
    return data_queue.empty();  
}
