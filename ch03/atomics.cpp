#include<thread>
#include<iostream>
#include<stdint.h>
#include<atomic>
#include<vector>

std::atomic<uint32_t> val_atomic;
uint32_t val_nonatomic;

void inc100Atomic(){
    for(uint32_t i=0;i<100;i++){
        val_atomic++;
    }
}

void inc100NonAtomic(){
    for(uint32_t i=0;i<100;i++){
        val_nonatomic++;
    }
}

int main()
{
    uint32_t num_cpus = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(num_cpus);

    for(uint32_t i=0;i<num_cpus;i++)
    {
        threads[i] = std::thread(inc100Atomic);
    }
    for(uint32_t i=0;i<num_cpus;i++)
    {
        threads[i].join();
    }
    for(uint32_t i=0;i<num_cpus;i++)
    {
        threads[i] = std::thread(inc100NonAtomic);
    }
    for(uint32_t i=0;i<num_cpus;i++)
    {
        threads[i].join();
    }
    std::cout<<val_atomic.load()<<" "<<val_nonatomic<<std::endl;
}
