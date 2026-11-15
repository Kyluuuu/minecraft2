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
        std::mutex tp_mutex;

        //All varaibles need to locked to access safely
        std::vector<std::thread> worker_threads;
        std::queue<std::function<void()>> tasks;
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
                        std::unique_lock<std::mutex> lock(tp_mutex);
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

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    ~ThreadPool() {
        {
            std::lock_guard<std::mutex> lock(tp_mutex);
            stop = true;
        }
        condition_variable.notify_all();
    }

    void addTask(void* task, ) {
        condition_variable.notify_one();
    }
    void joinTasks();



};