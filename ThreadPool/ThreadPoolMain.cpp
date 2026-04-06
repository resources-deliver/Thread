#include "Header.hpp"

int main(){
    ThreadPool pool(4);  // 创建线程池类对象,指定线程数量为4
    for(int i = 0; i < 8; i++){  // 循环添加8个任务到线程池
        pool.enqueue(  // 调用任务队列函数模板
            [i](){
                std::cout << "Task " << i << " is running in thread: " << std::this_thread::get_id() << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "Task " << i << " is done" << std::endl;
            }
        );
    }
    return 0;
}