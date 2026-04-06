# C++11 多线程Thread

## 简介

基于C++11标准库的多线程Thread编程，涵盖了线程基础操作、线程同步机制、异步任务处理以及线程池实现等核心内容。分为两个主要部分：
- **ThreadBase**: 线程基础操作与同步机制
- **ThreadPool**: 线程池实现与任务调度

## 开发环境

### 操作系统
- 支持 C++11 标准的任何现代操作系统（Windows、Linux、macOS 等）

### 开发工具
- 编译器：支持 C++11 标准的编译器
  - Windows: Visual Studio 2012 及以上版本 / MinGW-w64
  - Linux: GCC 4.8 及以上版本 / Clang 3.3 及以上版本
  - macOS: Clang 3.3 及以上版本
- IDE: Visual Studio / CLion / VSCode / 其他支持 C++ 的开发环境

## C++11 线程库核心概念

### 1. 线程基础
- **std::thread**: C++11 提供的线程类，用于创建和管理线程
- 线程控制：join()、detach()、joinable() 等
- this_thread 命名空间：提供当前线程相关的操作

### 2. 线程同步机制
- **互斥锁**: std::mutex、std::lock_guard、std::unique_lock、std::timed_mutex、std::recursive_mutex
- **条件变量**: std::condition_variable，用于线程间的等待与通知
- **原子操作**: std::atomic，提供无锁的线程安全操作

### 3. 异步任务
- **std::future 和 std::async**: 用于获取异步任务的结果
- **std::packaged_task**: 包装可调用对象，使其可以异步执行
- **std::promise**: 用于设置异步任务的结果

### 4. 智能指针与多线程
- **std::shared_ptr**: 共享所有权智能指针，线程安全的引用计数
- **std::weak_ptr**: 弱引用智能指针，避免循环引用

### 5. 线程池
- 线程池概念：工作线程集合、任务队列、线程同步机制、任务调度逻辑
- 线程池优势：降低开销、控制并发、提高效率、统一管理

## C++11 新特性在多线程中的应用

- **右值引用与移动语义**: std::move、移动构造函数和移动赋值运算符
- **lambda 表达式**: 匿名函数，用于创建线程任务
- **模板可变参数**: 支持任意数量和类型的参数
- **std::function 和 std::bind**: 函数包装器和参数绑定
- **RAII**: 使用对象的生命周期管理资源，自动管理锁

## 线程安全问题

- **数据竞态**: 多个线程同时访问共享数据，使用互斥锁或原子操作解决
- **死锁**: 多个线程互相等待对方释放锁，按固定顺序获取锁或使用 std::lock 解决
- **伪共享**: 多个线程访问同一缓存行的不同数据，通过数据对齐解决
- **条件变量虚假唤醒**: 在 wait 中使用条件判断

## 项目结构

```
Thread/
├── ThreadBase/           # 线程基础操作与同步机制
│   ├── ThreadClass.hpp   # 线程类定义
│   ├── ThreadContent.cpp # 线程类成员函数实现
│   └── ThreadFunc.cpp   # 线程函数演示
└── ThreadPool/           # 线程池实现
    ├── Header.hpp        # 线程池类定义
    ├── ThreadPoolFunc.cpp # 线程池函数实现
    └── ThreadPoolMain.cpp # 线程池使用示例
```

## 编译与运行

```bash
# 编译 ThreadBase
g++ -std=c++11 -pthread ThreadBase/ThreadContent.cpp ThreadBase/ThreadFunc.cpp -o threadbase

# 编译 ThreadPool
g++ -std=c++11 -pthread ThreadPool/ThreadPoolFunc.cpp ThreadPool/ThreadPoolMain.cpp -o threadpool

# 运行
./threadbase
./threadpool
```

## 许可证

本项目仅供学习交流使用。
