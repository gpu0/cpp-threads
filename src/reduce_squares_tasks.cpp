/**
* An example for tasks, futures and promises
*/

#include<iostream>
#include<thread>
#include<vector>
#include<future>

static int accum = 0;

int square(int x) {
  std::cout<<"Thead ID: "<<std::this_thread::get_id()<<std::endl;
  return x * x;
}

int main() {
  std::vector<std::future<int>> tasks;

  for(int i=1;i<=20;i++) {
/**
* With async, it gets executed as soon as std::async object is created
* Hence, it prints out thread id of spawned threads
*/
//    tasks.push_back(std::async(std::launch::async, &square,i));
/**
* With deferred, it executes at .get() routine
* Hence, it prints out thread id of main() function
*/
    tasks.push_back(std::async(std::launch::deferred, &square,i));
  }

  for(auto& task: tasks) {
    accum += task.get();
  }

  std::cout<<"accum = "<<accum<<std::endl;
}
