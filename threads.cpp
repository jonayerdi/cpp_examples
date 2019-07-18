#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

class semaphore
{
private:
    std::mutex mutex_;
    std::condition_variable condition_;
    size_t count_ = 0; // Initialized as locked.
public:
    semaphore(size_t count) : count_(count){}
    void notify(size_t count) {
        std::lock_guard<decltype(mutex_)> lock(mutex_);
        count_ += count;
        condition_.notify_all();
    }
    void wait(size_t count) {
        std::unique_lock<decltype(mutex_)> lock(mutex_);
        while(count_ < count) // Handle spurious wake-ups.
            condition_.wait(lock);
        count_ -= count;
    }
    bool try_wait(size_t count) {
        std::lock_guard<decltype(mutex_)> lock(mutex_);
        if(count_ >= count) {
            count_ -= count;
            return true;
        }
        return false;
    }
};

void incrementLoop(int& n, semaphore& signal_start) {
    signal_start.wait(1);
    for(size_t i = 0; i < 1000 ; ++i) {
        n += 1;
    }
}

int main() {
    constexpr size_t thread_count = 1000;
    std::vector<std::thread> threadList{};
    int n = 0;
    semaphore signal_threads{0};
    // print hardware concurrent threads count
    std::cout << std::thread::hardware_concurrency() << std::endl;
    // create threads
    for(size_t i = 0; i < thread_count ; ++i) {
        threadList.push_back(std::thread{incrementLoop, std::ref(n), std::ref(signal_threads)});
    }
    // wait a bit and signal all threads
    std::this_thread::sleep_for(std::chrono::seconds(1));
    signal_threads.notify(thread_count);
    // join and print result
    for(auto& t : threadList) {
        t.join();
    }
    std::cout << n << std::endl;
}
