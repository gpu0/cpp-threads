#include <iostream>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <mutex>
#include <pthread.h>
#include <thread>
#include <vector>

int main(int argc, const char* argv[]) {
    constexpr unsigned num_threads = 4;
    std::mutex iomutex;
    std::vector<std::thread> threads(num_threads);

    for(unsigned i=0;i<num_threads;i++) {
        threads[i] = std::thread([&iomutex, i] {
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
            while(1) {
                {
                    std::lock_guard<std::mutex> iolock(iomutex);
                    std::cout<<"Thread #"<<i<<": on CPU"<<sched_getcpu()<<"\n";
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(900));
            }
        });

        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(i, &cpuset);

        int rc = pthread_setaffinity_np(threads[i].native_handle(), sizeof(cpu_set_t), &cpuset);

        if(rc != 0) {
            std::cerr<< "Error calling pthread_setaffinity_np: "<<rc<<"\n";
        }
    }

    for(auto &t : threads) {
        t.join();
    }

    return 0;
}
