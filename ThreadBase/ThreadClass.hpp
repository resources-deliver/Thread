# ifndef THREADCLASS_HPP
# define THREADCLASS_HPP

#include <iostream>
#include <thread>  // 线程
#include <string>
#include <memory>  // 智能指针
#include <mutex>  // 线程互斥锁
#include <condition_variable>  // 条件变量
#include <queue>  // 队列
#include <future>  // 异步调用

class ThreadClass{
public:
    void funcC();
private:
    friend void threadFunction();  // 友元函数
    void funcD(std::string& str);
    void funcE();
    void funcF();
    void funcG();
    void funcH();
    void producer();
    void consumer();
    int funcI();
    void atomicOperator();
    std::mutex mtx, mtx1, mtx2, workMutex;  // 互斥锁
    std::timed_mutex delaydmtx;  // 延迟互斥锁
    std::condition_variable condVar;  // 条件变量做有关放取任务桥梁
    std::queue<int> workQueue;  // 任务队列
    int addData = 0;
    std::atomic<int> atomicData = 0;
};

void funcA();
void funcB(std::string& str);
void threadFunction();
# endif 