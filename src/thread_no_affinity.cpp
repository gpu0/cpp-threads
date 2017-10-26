#include <iostream>
#include <algorithm>
#include <chrono>
#include <mutex>
#include <sched.h>
#include <thread>
#include <vector>

int main(int argc, const char* argv[]) {
    constexpr unsigned num_threads = 4;

    std::mutex iomutex;
    std::vector<std::thread> threads(num_threads);

    for(int i=0;i<num_threads;i++) {
        threads[i] = std::thread([&iomutex, i] {
            while(1) {
                {
                    std::lock_guard<std::mutex> iolock(iomutex);
                    std::cout<<"Thread #" <<i<<": on CPU "<<sched_getcpu()<<" \n";
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(900));
            }
        });
    }

    for(auto& t: threads) {
        t.join();
    }
    return 0;
}
