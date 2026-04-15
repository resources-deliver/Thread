#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <queue>

// 线程池类
class ThreadPool{
public:
    ThreadPool(int threadcount);
    ~ThreadPool();
public:
    void threadWork();
    template<typename F, typename... Args>
    void enqueue(F&& f, Args&&... args);
private:
    std::vector<std::thread> threadvector;
    std::queue<std::function<void()>> workqueue;
    std::mutex mutex;
    std::condition_variable condition;
    bool stop;
};

// 任务队列函数模板: 将任务放到任务队列中并通知线程池有任务到来
template<typename F, typename... Args>
void ThreadPool::enqueue(F&& f, Args&&... args){
    std::function<void()> task(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    {  // 锁作用域
        std::unique_lock<std::mutex> lock(mutex);  // 自动加锁解锁
        workqueue.emplace(std::move(task));  // 放任务到队列
    }
    condition.notify_one();  // 通知1个线程取任务
}

#endif // HEADER_HPP