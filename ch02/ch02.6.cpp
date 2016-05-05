#include<iostream>
#include<vector>
#include<thread>
#include<stdint.h>

std::thread::id parentThreadId;

class Printer{
public:
	void Print()
	{
		std::cout<<"Current Thread Id is: "<<std::this_thread::get_id()<<std::endl;
		if(std::this_thread::get_id() == parentThreadId)
		{
			std::cout<<"Hello Master Thread"<<std::endl;
		}
		else
		{
			std::cout<<"Hello Thread"<<std::endl;
		}
	}
};

int masterFunction()
{
	parentThreadId = std::this_thread::get_id();
	uint32_t num_cpus = std::thread::hardware_concurrency();
	std::vector<std::thread>threads(num_cpus);

	for(uint32_t i=0;i<num_cpus;i++){
		Printer printer;
		threads[i] = std::thread(&Printer::Print, &printer);
	}

	for(uint32_t i=0;i<num_cpus;i++){
		threads[i].join();
	}
}

int main()
{
	std::thread parentThread(masterFunction);
	parentThread.join();
	Printer printer;
	parentThread = std::thread(&Printer::Print, &printer);
	parentThread.join();
}
