/**
* An example for race-condition
* accum can have partial data
* convert it to atomic to get correct data
*/

#include<iostream>
#include<thread>
#include<vector>

static int accum = 0;

void square(int x) {
  accum += x * x;
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
