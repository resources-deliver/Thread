#include "Header.hpp"

// 构造函数: 创建线程池并启动线程
ThreadPool::ThreadPool(int threadcount): stop(false){
    for(int i = 0; i < threadcount; i++){  // 循环创建threadcount个线程
        std::thread pushtovec(&ThreadPool::threadWork, this);  // 创建线程
        threadvector.emplace_back(std::move(pushtovec));  // 存放到线程数组(thread类删除了拷贝构造,只能采用转右值)
    }
}

// 线程工作函数: 线程不断循环取任务并执行
void ThreadPool::threadWork(){
    while(true){  // 线程不断循环取任务并执行
        std::unique_lock<std::mutex> lock(mutex);  // 自动加锁解锁
        // 等待条件变量通知任务到来(任务队列不为空)或者线程池停止
        condition.wait(lock, [this](){ return stop || !workqueue.empty(); });
        if(stop && workqueue.empty()) return;  // 线程池停止且任务队列为空,退出线程
        auto work = workqueue.front();  // 取任务
        std::function<void()> task(std::move(work));  // 任务包装成函数
        workqueue.pop();  // 删除任务
        // lock.unlock();  // 手动解锁,让其他线程可以继续访问任务队列
        task();  // 通过函数执行任务
    }
}

// 析构函数: 停止线程池并等待线程结束
ThreadPool::~ThreadPool(){
    {  // 锁作用域
        std::unique_lock<std::mutex> lock(mutex);  // 自动加锁解锁
        stop = true;  // 线程池停止
    }
    condition.notify_all();  // 条件变量通知所有线程取任务
    // 遍历线程池,阻塞等待每个线程执行完毕
    for(auto& thread: threadvector){
        if(thread.joinable()){
            thread.join();
        }
    }
}