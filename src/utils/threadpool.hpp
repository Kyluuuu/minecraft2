#pragma once

#include <condition_variable>
#include <vector>
#include <queue>
#include <mutex>
#include <thread>
#include <functional>
#include <future>
#include <memory>
#include <type_traits>

class ThreadPool {
    private:
        std::vector<std::thread> worker_threads;
        std::queue<std::function<void()>> tasks;
        std::mutex mutex;
        std::condition_variable condition_variable;
        bool stop{false};

    
    public:

    explicit ThreadPool(int n = std::thread::hardware_concurrency()) {

        for (int i = 0; i < n; i++) 
        {
            worker_threads.emplace_back([this] {
                while (true) 
                {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(mutex);
                        condition_variable.wait(lock, [this] { return stop || !tasks.empty(); });
                        if (stop && tasks.empty()) return;
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    ~ThreadPool() {

    }

    void addTask(void* task, ) {
        condition_variable.notify_one();
    }
    void joinTasks();



};