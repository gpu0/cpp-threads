#include<thread>
#include<iostream>
#include<stdint.h>
#include<vector>
#include<ctime>
#include<atomic>
#include<mutex>

#define ITER 1 << 20

uint32_t val;
std::atomic<uint32_t> val_atomic;
std::mutex lock;

void inc()
{
    std::lock_guard<std::mutex> guard(lock);
    val++;
}

void incWithLock()
{
    for(uint32_t i=0;i<ITER;i++)
    {
        inc();
    }
}

void incWithAtoms()
{
    for(uint32_t i=0;i<ITER;i++)
    {
        val_atomic++;
    }
}

int main()
{
    uint32_t num_cpus = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(num_cpus);
    clock_t start, stop;
    double run_time;
    start = clock();
    for(uint32_t i=0;i<num_cpus;i++)
    {
        threads[i] = std::thread(incWithAtoms);
    }
    for(uint32_t i=0;i<num_cpus;i++)
    {
        threads[i].join();
    }
    stop = clock();
    run_time = (double)(stop - start)/CLOCKS_PER_SEC;
    std::cout<<"Atomics took: "<<run_time<<std::endl;
    start = clock();
    for(uint32_t i=0;i<num_cpus;i++)
    {
        threads[i] = std::thread(incWithLock);
    }
    for(uint32_t i=0;i<num_cpus;i++)
    {
        threads[i].join();
    }
    stop = clock();
    run_time = (double)(stop - start)/CLOCKS_PER_SEC;
    std::cout<<"Locks took: "<<run_time<<std::endl;
}
