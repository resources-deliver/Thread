#include "ThreadClass.hpp"

void threadFunction(){
    std::thread t1(funcA);  // 创建线程并进入(无参函数)
    if(t1.joinable()) t1.join();  // 主线程等待子线程结束

    std::string str("Hello Thread");
    std::thread t2(funcB, std::ref(str));  // 创建线程并进入(含参函数)
    if(t2.joinable()) t2.join();

    // 共享智能指针创建方式1:shared_ptr类模板中make_shared函数模板为参数的构造函数
    std::shared_ptr<ThreadClass> point(std::make_shared<ThreadClass>());
    // 共享智能指针创建方式2:shared_ptr类模板中原始指针为参数的构造函数
    // ThreadClass* init_point = new ThreadClass();  // 创建原始指针并初始化
    // std::shared_ptr<ThreadClass> point(init_point);  // 创建共享智能指针并初始化

    std::thread t3(&ThreadClass::funcC, point);  // 创建线程并进入(类内公有无参函数)
    if(t3.joinable()) t3.join();
    std::cout << "addData = " << point->addData << std::endl;

    std::thread t4(&ThreadClass::funcD, point, ref(str));;  // 创建线程并进入(类内私有含参函数)
    if(t4.joinable()) t4.join();
    std::cout << "addData = " << point->addData << std::endl;

    // 多线程数据共享问题(互斥锁)
    std::thread t5_1(&ThreadClass::funcE, point);
    std::thread t5_2(&ThreadClass::funcE, point);
    if(t5_1.joinable()) t5_1.join();
    if(t5_2.joinable()) t5_2.join();
    std::cout << "addData = " << point->addData << std::endl;

    // 多线程数据共享问题(原子操作)
    std::thread t5_3(&ThreadClass::atomicOperator, point);
    std::thread t5_4(&ThreadClass::atomicOperator, point);
    if(t5_3.joinable()) t5_3.join();
    if(t5_4.joinable()) t5_4.join();
    std::cout << "atomicData = " << point->atomicData << std::endl;

    // 多线程多互斥量数据共享问题(死锁)
    std::thread t6_1(&ThreadClass::funcF, point);
    std::thread t6_2(&ThreadClass::funcG, point);
    if(t6_1.joinable()) t6_1.join();
    if(t6_2.joinable()) t6_2.join();
    std::cout << "addData = " << point->addData << std::endl;

    // 多线程数据共享问题(延迟加锁)
    std::thread t7_1(&ThreadClass::funcH, point);
    std::thread t7_2(&ThreadClass::funcH, point);
    if(t7_1.joinable()) t7_1.join();
    if(t7_2.joinable()) t7_2.join();
    std::cout << "addData = " << point->addData << std::endl;

    // 条件变量
    std::thread t8_1(&ThreadClass::producer, point);
    std::thread t8_2(&ThreadClass::consumer, point);
    if(t8_1.joinable()) t8_1.join();
    if(t8_2.joinable()) t8_2.join();

    // 异步
    std::future<int> future_result(std::async(std::launch::async, &ThreadClass::funcI, point));  // 创建异步任务并进入
    int now_addData = point->funcI();
    std::cout << "now addData = " << now_addData << std::endl;
    int wait_async = future_result.get();  // 等待异步任务结束并获取
    std::cout << "addData = " << wait_async << std::endl;
}

int main(){
    threadFunction();
    return 0;
}