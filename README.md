# Thread

此目录包含演示 C++ 线程、互斥、条件变量、异步和线程池的示例代码。

结构概览：
- `ThreadBase/`：基础线程示例，展示 `std::thread`、互斥锁、条件变量、`std::async`/`future`/`promise`/`packaged_task` 等。
- `ThreadPool/`：简单线程池实现，包含任务入队模板和线程工作循环。

构建（在各子目录使用）：

```bash
# 编译ThreadBase
g++ -std=c++11 -Wall ThreadBase/*.cpp -o ./Compiled/ThreadBase

# 编译ThreadPool
g++ -std=c++11 -Wall ThreadPool/*.cpp -o ./Compiled/ThreadPool
```

运行：

```bash
./ThreadBase/ThreadBase
./ThreadPool/ThreadPool
```

说明：使用C++11及以上特性可视需要调整编译器标准为C++14或C++17。
