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
class join_threads
{
    public:
        explicit join_threads(std::vector<std::thread>& threads_);
        ~join_threads();
    private:
        std::vector<std::thread>& threads;

};

/**
 * @brief STL queue wrapper = thread safe queue to do standard operations atomically and
 * relativaely safe compared to stl queue
 * 
 * @tparam T 
 */
template <typename T>
class thread_safe_queue
{
    public:
        thread_safe_queue() = default;
        thread_safe_queue(thread_safe_queue const& other);
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
 * @brief Class for automatically managing tasks and 
 * distribute them between maximum of hw - supported number
 * of threads.
 * 
 */
class thread_pool
{
    public:
        thread_pool();
        ~thread_pool();

        template <typename FuncType> void submit(FuncType f);

    private:
        std::atomic<bool> done;
        thread_safe_queue<std::function<void()>> work_queue;
        std::vector<std::thread> threads;
        join_threads joiner;
        void worker_thread();
};



/**
 * @brief Construct a new thread safe queue<T>::thread safe queue object
 * 
 * @tparam T 
 * @param other 
 */
template <typename T>
thread_safe_queue<T>::thread_safe_queue(const thread_safe_queue<T> & other)
{
    std::lock_guard<std::mutex> lk (other.mut);
    data_queue = other.data_queue;
}

/**
 * @brief Atomically push new queue member to the end of list 
 * 
 * @tparam T 
 * @param new_value 
 */
template <typename T>
void thread_safe_queue<T>::push(T new_value)
{
    std::lock_guard<std::mutex> lk(mut);
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
void thread_safe_queue<T>::wait_and_pop(T& value)
{
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this]{return !data_queue.empty();});
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
bool thread_safe_queue<T>::try_pop(T& value)
{
    std::lock_guard<std::mutex>lk (mut);
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
bool thread_safe_queue<T>::empty() const
{
    std::lock_guard<std::mutex> lk(mut);
    return data_queue.empty();  
}

/**
 * @brief Submit new task for threads to do
 * 
 * @tparam FuncType 
 * @param f 
 */
template <typename FuncType>
void thread_pool::submit(FuncType f)
{
    work_queue.push(std::function<void()>(f));
}

