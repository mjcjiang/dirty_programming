#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>
#include <chrono>

std::mutex mut;
std::condition_variable data_cond;
std::queue<int> data_queue;

void data_preparation_thread() {
    std::lock_guard<std::mutex> lk(mut);
    data_queue.push(10);
    std::cout << "finish push" << std::endl;
    data_cond.notify_one();
}

void data_processing_thread() {
    std::unique_lock<std::mutex> lk{mut, std::defer_lock};
    data_cond.wait(lk, []{return !data_queue.empty();});
    int data = data_queue.front();
    data_queue.pop();
    lk.unlock();
    std::cout << "Processing data: " << data << std::endl;
}

int main(int argc, char *argv[])
{
    std::thread t1(data_processing_thread);
    std::thread t2(data_processing_thread);
    t1.join();
    t2.join();
    return 0;
}
