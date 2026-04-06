#include "ThreadClass.hpp"

void threadFunction(){
    // 线程创建(类外无参函数)
    std::thread t1(funcA);
    if(t1.joinable()) t1.join();  // 主线程等待子线程结束
    std::cout << "thread1 over" << std::endl;

    // 线程创建(类外含参函数)
    std::string str("Hello Thread");
    std::thread t2(funcB, std::ref(str));
    if(t2.joinable()) t2.join();
    std::cout << "thread2 over" << std::endl;

    // 共享智能指针创建:shared_ptr类模板构造函数(make_shared函数模板为参数)
    std::shared_ptr<ThreadClass> point(std::make_shared<ThreadClass>());  // 类指针对象

    // 线程创建(类内无参函数)
    std::thread t3(&ThreadClass::funcC, point);
    if(t3.joinable()) t3.join();
    std::cout << "addData(thread3): " << point->addData << std::endl;

    // 线程创建(类内含参函数)
    std::thread t4(&ThreadClass::funcD, point, std::ref(str));
    if(t4.joinable()) t4.join();
    std::cout << "addData(thread4): " << point->addData << std::endl;

    // 多线程数据共享问题(互斥锁)
    std::thread t5_1(&ThreadClass::addLock, point);
    std::thread t5_2(&ThreadClass::addLock, point);
    if(t5_1.joinable()) t5_1.join();
    if(t5_2.joinable()) t5_2.join();
    std::cout << "addData(mutex lock): " << point->addData << std::endl;

    // 多线程数据共享问题(原子操作)
    std::thread t5_3(&ThreadClass::atomicOperator, point);
    std::thread t5_4(&ThreadClass::atomicOperator, point);
    if(t5_3.joinable()) t5_3.join();
    if(t5_4.joinable()) t5_4.join();
    std::cout << "atomicData(atomic operator): " << point->atomicData << std::endl;

    // 多线程多互斥量数据共享问题(死锁)
    std::thread t6_1(&ThreadClass::deadLock1, point);
    std::thread t6_2(&ThreadClass::deadLock2, point);
    if(t6_1.joinable()) t6_1.join();
    if(t6_2.joinable()) t6_2.join();
    std::cout << "addData(dead lock): " << point->addData << std::endl;

    // 多线程数据共享问题(延迟加锁)
    std::thread t7_1(&ThreadClass::delayLock, point);
    std::thread t7_2(&ThreadClass::delayLock, point);
    if(t7_1.joinable()) t7_1.join();
    if(t7_2.joinable()) t7_2.join();
    std::cout << "addData(delay lock): " << point->addData << std::endl;

    // 条件变量
    std::thread t8_1(&ThreadClass::producer, point);
    std::thread t8_2(&ThreadClass::consumer, point);
    if(t8_1.joinable()) t8_1.join();
    if(t8_2.joinable()) t8_2.join();
    std::cout << "condition_variable over" << std::endl;

    // future异步
    std::future<int> create_task(
        std::async(
            std::launch::async, 
            &ThreadClass::asyncTask, 
            point
        )
    );  // 创建异步任务并调用
    auto pthread_got = point->asyncTask();  // 主线程调用
    std::cout << "addData(Pthread): " << pthread_got << std::endl;  // 主线程调用结果
    auto task_result = create_task.get();  // 等待异步任务结束并获取
    std::cout << "addData(Future): " << task_result << std::endl;  // 异步任务调用结果

    // packaged_task异步
    std::function<int()> packtofunc(std::bind(&ThreadClass::asyncTask, point));  // 包装成函数
    std::packaged_task<int()> create_task2(packtofunc);  // 创建异步任务
    auto get_task2 = create_task2.get_future();     // 获取异步任务
    std::thread t9(std::move(create_task2));        // 通过线程调用异步任务
    auto pthread_got2 = point->asyncTask();  // 主线程调用
    std::cout << "addData(Pthread): " << pthread_got2 << std::endl;  // 主线程调用结果
    if(t9.joinable()) t9.join();       // 等待异步线程结束
    auto task_result2 = get_task2.get();  // 等待异步任务结束并获取
    std::cout << "addData(Packaged_Task): " << task_result2 << std::endl;  // 异步任务调用结果

    // promise异步
    std::promise<int> create_task3;  // 创建异步任务
    auto get_task3 = create_task3.get_future();  // 获取异步任务
    std::thread t10(&ThreadClass::asyncTaskPromise, point, std::move(create_task3));  // 通过线程调用异步任务
    if(t10.joinable()) t10.join();  // 等待异步线程结束
    auto task_result3 = get_task3.get();  // 等待异步任务结束并获取
    std::cout << "addData(Promise): " << task_result3 << std::endl;  // 异步任务调用结果
}

int main(){
    threadFunction();
    return 0;
}