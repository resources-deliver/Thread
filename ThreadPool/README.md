# ThreadPool

目的：实现一个简单的线程池 `ThreadPool`，展示任务入队、线程工作循环、条件变量唤醒与关闭。

主要文件：
- `Header.hpp`：`ThreadPool` 类声明与 `enqueue` 任务模板实现。
- `ThreadPoolFunc.cpp`：线程池构造、工作循环与析构时的停止逻辑实现。
- `ThreadPoolMain.cpp`：演示如何创建一个 `ThreadPool` 并向其中提交任务。

特性说明：
- 使用 `std::vector<std::thread>` 存储工作线程，使用 `std::queue<std::function<void()>>` 存任务。
- `enqueue` 使用模板将任意可调用对象和参数封装为 `std::function<void()>` 并入队，随后调用 `condition.notify_one()`。
- 工作线程通过 `condition.wait` 等待任务或停止标志，取到任务后执行。
- 析构函数设置 `stop = true`，`notify_all()`，并 `join()` 所有线程，保证退出。

构建：

```bash
g++ -std=c++11 -Wall ThreadPool/*.cpp -o ./Compiled/ThreadPool
```

运行：

```bash
./ThreadPool
```
