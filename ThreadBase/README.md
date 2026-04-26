# ThreadBase 示例

目的：展示C++中常见的线程用法与并发控制，包括线程创建方式、互斥锁、死锁示例、延迟加锁、条件变量、生产者/消费者、原子操作及多种异步机制。

主要文件：
- `ThreadClass.hpp`：类定义，包含示例方法：`funcC`, `funcD`, `addLock`, `deadLock1`, `deadLock2`, `delayLock`, `producer`, `consumer`, `asyncTask`, `asyncTaskPromise`, `atomicOperator` 等。
- `ThreadContent.cpp`：`ThreadClass` 方法实现。
- `ThreadFunc.cpp`：示例入口，`threadFunction()` 展示：
  - 通过函数指针创建线程（无参/有参）
  - 通过 `std::shared_ptr` 创建并传递成员函数给线程
  - 互斥锁与原子操作对比
  - 死锁示例（`deadLock1` / `deadLock2`）
  - 延迟加锁示例 (`try_lock_for`)
  - 条件变量生产者/消费者示例
  - `std::async` / `future`、`packaged_task`、`promise` 等异步范例

构建：

```bash
g++ -std=c++11 -Wall ThreadBase/*.cpp -o ./Compiled/ThreadBase
```

运行：

```bash
./ThreadBase
```
