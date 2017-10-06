/**
* An example for using mutex
*/

#include<iostream>
#include<thread>
#include<vector>
#include<mutex>

static int accum = 0;
std::mutex accum_mutex;

void square(int x) {
  auto tmp = x * x;
  accum_mutex.lock();
  accum += tmp;
  accum_mutex.unlock();
}

int main() {
  std::vector<std::thread> ths;

  for(int i=1;i<=20;i++) {
    ths.push_back(std::thread(&square,i));
  }

  for(auto& th: ths) {
    th.join();
  }

  std::cout<<"accum = "<<accum<<std::endl;
}
