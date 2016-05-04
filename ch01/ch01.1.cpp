/*
 Chapter 01

 This file tries to find number of Threads available on CPU
 and use all of them to compute SaXpY.

 Each element is operated on by a thread.
*/

#include<iostream>
#include<thread>
#include<vector>
#include<stdint.h>

void saxpy(float *S, float a, float X, float b, float Y)
{
	*S = a*X + b*Y;
}

int main()
{
	unsigned num_cpus = std::thread::hardware_concurrency();

	std::cout<<"Number of available threads: "<<num_cpus<<std::endl;

	float *S = new float[num_cpus];
	float *X = new float[num_cpus];
	float *Y = new float[num_cpus];
	float a = 1.0f, b = 2.0f;

	std::vector<std::thread>threads(num_cpus);

	for(uint32_t i=0;i<num_cpus;i++)
	{
		X[i] = i*1.0f;
		Y[i] = (i+1)*1.0f;
		threads[i] = std::thread(saxpy, S+i, a, X[i], b, Y[i]);
	}

	for(int i=0;i<num_cpus;i++)
	{
		threads[i].join();
		std::cout<< S[i] << std::endl;
	}
}
