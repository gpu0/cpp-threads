#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <queue>
using namespace std;

mutex goods_mutex;

int main() {
  int c = 0;
  bool done = false;
  queue<int> goods;

  thread producer([&]() {
    for (int i = 0; i < 500; ++i) {
      goods_mutex.lock();
      goods.push(i);
      c++;
      goods_mutex.unlock();
    }
  done = true;
  });

  thread consumer([&]() {
    while (!done) {
      while (!goods.empty()) {
        goods_mutex.lock();
        goods.pop();
        c--;
        goods_mutex.unlock();
      }
    }
  });

  producer.join();
  consumer.join();
  cout << "Net: " << c << endl;
}
