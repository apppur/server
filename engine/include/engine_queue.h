#ifndef _ENGINE_QUEUE_H_
#define _ENGINE_QUEUE_H_

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

template <typename T>
class engine_queue {
    public:
        T pop() {
            std::unique_lock<std::mutex> tmutex(m_mutex);
            while (m_queue.empty()) {
                m_cond.wait(tmutex);
            }
            auto item = m_queue.front();
            m_queue.pop();
            return item;
        }

        void pop(T& item) {
            std::unique_lock<std::mutex> tmutex(m_mutex);
            while (m_queue.empty()) {
                m_cond.wait(tmutex);
            }
            item = m_queue.front();
            m_queue.pop();
        }

        void push(T& item) {
            std::unique_lock<std::mutex> tmutex(m_mutex);
            m_queue.push(item);
            tmutex.unlock();
            m_cond.notify_one();
        }
        void push(T&& item) {
            std::unique_lock<std::mutex> tmutex(m_mutex);
            m_queue.push(std::move(item));
            tmutex.unlock();
            m_cond.notify_one();
        }
    private:
        std::queue<T> m_queue;
        std::mutex m_mutex;
        std::condition_variable m_cond;
};

#endif
