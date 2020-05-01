/**
 * An example for atomics
 */

#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

std::atomic<int> accum(0);

void square(int x) { accum += x * x; }

int main() {
  std::vector<std::thread> ths;

  for (int i = 1; i <= 20; i++) {
    ths.push_back(std::thread(&square, i));
  }

  for (auto& th : ths) {
    th.join();
  }

  std::cout << "accum = " << accum << std::endl;
}
