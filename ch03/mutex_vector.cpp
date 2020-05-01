#include <stdint.h>

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::vector<uint32_t> data;
std::mutex lock;
void append(uint32_t val) {
  std::lock_guard<std::mutex> guard(lock);
  data.push_back(val);
}

int main() {
  uint32_t num_cpus = std::thread::hardware_concurrency();
  std::vector<std::thread> threads(num_cpus);
  for (uint32_t i = 0; i < num_cpus; i++) {
    threads[i] = std::thread(append, i);
  }
  for (uint32_t i = 0; i < num_cpus; i++) {
    threads[i].join();
  }
  for (uint32_t i = 0; i < num_cpus; i++) {
    std::cout << data[i] << std::endl;
  }
}
