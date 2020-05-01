#include <stdint.h>

#include <atomic>
#include <ctime>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#define ITER 1 << 20

uint32_t val;
std::atomic<uint32_t> val_atomic;
std::mutex lock;

void inc() {
  std::lock_guard<std::mutex> guard(lock);
  val++;
}

void incWithLockCons() {
  for (uint32_t i = 0; i < ITER; i++) {
    inc();
  }
}

void incWithLockNoCons() {
  for (uint32_t i = 0; i < ITER; i++) {
    lock.lock();
    val++;
    lock.unlock();
  }
}

void incWithAtoms() {
  for (uint32_t i = 0; i < ITER; i++) {
    val_atomic++;
  }
}

int main() {
  uint32_t num_cpus = std::thread::hardware_concurrency();
  std::vector<std::thread> threads(num_cpus);
  clock_t start, stop;
  double run_time;

  // For Atomics
  start = clock();
  for (uint32_t i = 0; i < num_cpus; i++) {
    threads[i] = std::thread(incWithAtoms);
  }
  for (uint32_t i = 0; i < num_cpus; i++) {
    threads[i].join();
  }
  stop = clock();
  run_time = (double)(stop - start) / CLOCKS_PER_SEC;
  std::cout << "Atomics took: " << run_time << std::endl;

  // For Locks without Constructor
  start = clock();
  for (uint32_t i = 0; i < num_cpus; i++) {
    threads[i] = std::thread(incWithLockNoCons);
  }
  for (uint32_t i = 0; i < num_cpus; i++) {
    threads[i].join();
  }
  stop = clock();
  run_time = (double)(stop - start) / CLOCKS_PER_SEC;
  std::cout << "Locks without Cons: " << run_time << std::endl;

  // For Locks with Constructor
  start = clock();
  for (uint32_t i = 0; i < num_cpus; i++) {
    threads[i] = std::thread(incWithLockCons);
  }
  for (uint32_t i = 0; i < num_cpus; i++) {
    threads[i].join();
  }
  stop = clock();
  run_time = (double)(stop - start) / CLOCKS_PER_SEC;
  std::cout << "Locks with Cons: " << run_time << std::endl;
}
