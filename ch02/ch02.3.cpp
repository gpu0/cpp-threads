#include<iostream>
#include<vector>
#include<thread>
#include<stdint.h>

class threadGuard
{
public:
	std::thread &t;
	threadGuard(std::thread &t) : t(t) {}
	~threadGuard()
	{
		if(t.joinable())
		{
			t.join();
		}
	}
//	threadGuard(threadGuard const&)=delete;
	threadGuard& operator=(threadGuard const&)=delete;
};

void Saxpy(float *S, float a, float X, float b, float Y) {
	*S = a*X + b*Y;
}

int main()
{
	uint32_t numCpus = std::thread::hardware_concurrency();
	std::vector<threadGuard>threads;

	float *S = new float[numCpus], a = 1.0f, *X = new float[numCpus], b = 2.0f, *Y = new float[numCpus];

	for(uint32_t i=0;i< numCpus;i++)
	{
		X[i] = 1.0f*i;
		Y[i] = (i+1)*2.0f;
		std::thread t = std::thread(Saxpy, S+i, a, X[i], b, Y[i]);
		threads.push_back(threadGuard(t));
	}
	for(uint32_t i=0;i<numCpus;i++){
		std::cout<<S[i]<<std::endl;
	}
}
