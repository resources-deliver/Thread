#include "ThreadClass.hpp"

void funcA(){
    std::cout << "FUNCTIONA" << std::endl;
}

void funcB(std::string& str){
    std::cout << "functionB, parameter: " << str << std::endl;
}

void ThreadClass::funcC(){
    for(int i = 0; i < 10; i++){
        addData += 1;
    }
}

void ThreadClass::funcD(std::string& str){
    for(int i = 0; i < 10; i++){
        addData += 1;
    }
}

// 对于多个线程同时访问共享数据时,使用互斥锁,保证同一时刻只有一个线程访问共享数据,避免数据竞态
void ThreadClass::addLock(){
    for(int i = 0; i < 10; i++){
        // std::lock_guard<std::mutex> lock(mtx);  // 使用lock_guard自动加锁解锁
        // std::unique_lock<std::mutex> lock(mtx);  // 使用unique_lock自动加锁解锁
        mtx.lock();  // 手动上锁
        addData += 1;
        mtx.unlock();  // 手动解锁
    }
}

// 对于多个线程同时访问共享数据时,如果共享数据为原子类模板对象,则无需考虑加锁以及数据竞态
void ThreadClass::atomicOperator(){
    for(int i = 0; i < 10; i++){
        atomicData += 1;
    }
}

// 对于多个线程同时访问共享数据时,使用互斥锁,保证同一时刻只有一个线程访问共享数据,避免数据竞态
// 加锁数量与顺序以及加相同锁需要一致
void ThreadClass::deadLock1(){
    for(int i = 0; i < 10; i++){
        std::unique_lock<std::mutex> lock1(mtx1);
        std::unique_lock<std::mutex> lock2(mtx2);
        addData += 1;
    }
}
void ThreadClass::deadLock2(){
    for(int i = 0; i < 10; i++){
        std::unique_lock<std::mutex> lock1(mtx1);
        std::unique_lock<std::mutex> lock2(mtx2);
        addData += 1;
    }
}

// 对于多个线程同时访问共享数据时,使用互斥锁,保证同一时刻只有一个线程访问共享数据,避免数据竞态
// 延迟加锁
void ThreadClass::delayLock(){
    for(int i = 0; i < 10; i++){
        std::unique_lock<std::timed_mutex> lock(delaydmtx, std::defer_lock);  // 不加锁只解锁
        if(lock.try_lock_for(std::chrono::seconds(1))){  // 延迟1秒加锁
            addData += 1;
        }
        else{
            std::cout << "延迟加锁失败" << std::endl;
        }
    }
}

void ThreadClass::producer(){
    for(int i = 0; i < 10; i++){
        {  // 互斥锁作用域
            std::unique_lock<std::mutex> lock(workMutex);  // 互斥锁自动加锁解锁
            addData += 1;
            workQueue.push(addData);  // 放任务到队列
            std::cout << "生产者放进去的任务: " << addData << std::endl;
            condVar.notify_one();  // 通知1个线程取任务
            // condVar.notify_all();  // 通知所有线程取任务
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // 休眠100毫秒,模拟生产者生产任务的时间间隔
    }
}
void ThreadClass::consumer(){
    for(int i = 0; i < 10; i++){
        std::unique_lock<std::mutex> lock(workMutex);  // 互斥锁自动加锁解锁
        condVar.wait(lock, [this]{ return !workQueue.empty(); });  // 等待条件变量通知任务到来(任务队列不为空)
        int work = workQueue.front();  // 取任务
        workQueue.pop();  // 删除任务
        std::cout << "消费者取出来的任务: " << work << std::endl;
    }
}

// 异步任务
int ThreadClass::asyncTask(){
    for(int i = 0; i < 10; i++){
        addData += 1;
    }
    return addData;
}

void ThreadClass::asyncTaskPromise(std::promise<int>&& prom){
    for(int i = 0; i < 10; i++){
        addData += 1;
    }
    prom.set_value(addData);  // 设置异步任务结果
}