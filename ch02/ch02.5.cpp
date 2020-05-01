#include <stdint.h>

#include <iostream>
#include <thread>
#include <vector>

class Printer {
public:
  void Print() { std::cout << "Hello Thread" << std::endl; }
};

int main() {
  uint32_t num_cpus = std::thread::hardware_concurrency();
  std::vector<std::thread> threads(num_cpus);

  for (uint32_t i = 0; i < num_cpus; i++) {
    Printer printer;
    threads[i] = std::thread(&Printer::Print, &printer);
  }

  for (uint32_t i = 0; i < num_cpus; i++) {
    threads[i].join();
  }
}
