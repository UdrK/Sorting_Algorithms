#include <mutex>
#include <condition_variable>
#include <deque>

#ifndef THREADSAFEQUEUE_H
#define THREADSAFEQUEUE_H

template <class T>
class ThreadsafeQueue {
    public:
        void push(T);
        T pop();
        bool tryPop (T & v, std::chrono::milliseconds dur);
        int size();
    private:
        std::mutex              d_mutex;
        std::condition_variable d_condition;
        std::deque<T>           d_queue;
};

// PUBLIC --------------------------------------------------------------------

template <class T>
void ThreadsafeQueue<T>::push(T value) {
    {
        std::unique_lock<std::mutex> lock(this->d_mutex);
        d_queue.push_front(value);
    }
    this->d_condition.notify_one();
}

template <class T>
T ThreadsafeQueue<T>::pop() {
    std::unique_lock<std::mutex> lock(this->d_mutex);
    this->d_condition.wait(lock, [=]{ return !this->d_queue.empty(); });
    T rc(std::move(this->d_queue.back()));
    this->d_queue.pop_back();
    return rc;
}

template <class T>
bool ThreadsafeQueue<T>::tryPop (T & v, std::chrono::milliseconds dur) {
    std::unique_lock<std::mutex> lock(this->d_mutex);
    if (!this->d_condition.wait_for(lock, dur, [=]{ return !this->d_queue.empty(); })) {
        return false;
    }
    v = std::move (this->d_queue.back());
    this->d_queue.pop_back();
    return true;
}

template <class T>
int ThreadsafeQueue<T>::size() {
    return d_queue.size();
}

#endif