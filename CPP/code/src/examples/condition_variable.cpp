
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

volatile int g_val = 0; // 全局变量，供线程间通信使用
std::mutex mtx;
std::condition_variable cv;

// 消费者：等待资源
void consumer() {
    std::unique_lock lk(mtx);
    std::cout << "[Consumer] 等待资源...\n";
    // 使用带谓词的 wait，防止虚假唤醒或错过通知
    cv.wait(lk, []{ return (g_val == 1); });
    // 唤醒后一定拿到了锁，且 ready == true
    std::cout << "[Consumer] 获得资源，开始消费。\n";
}

// 生产者：准备资源并通知
void producer() {
    // 模拟生产耗时
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    std::scoped_lock slk(mtx);
    g_val += 1;
    std::cout << "[Producer] 资源已准备好，发出通知。\n";
    
    cv.notify_one();  // 通知一个等待线程
}

int main() {

    std::thread t_consumer(consumer);
    std::thread t_producer(producer);

    t_consumer.join();
    t_producer.join();
    return 0;
}
