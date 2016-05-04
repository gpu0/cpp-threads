/*
 What if you dont want to wait until thread is finished
*/

#include<iostream>
#include<vector>
#include<thread>
#include<stdint.h>

void Saxpy(float *S, float a, float X, float b, float Y)
{
	*S = a*X + b*Y;
}

int main()
{
	uint32_t num_cpus = std::thread::hardware_concurrency();
	std::vector<std::thread>threads(num_cpus);

	float *S = new float[num_cpus], a = 1.0f, b = 2.0f, *X = new float[num_cpus], *Y = new float[num_cpus];

	for(uint32_t i=0;i<num_cpus;i++){
		X[i] = 1.0f*i;
		Y[i] = 2.0f*(i+1);
		threads[i] = std::thread(Saxpy, S+i, a, X[i], b, Y[i]);
	}

	for(uint32_t i=0;i<num_cpus;i++){
		threads[i].detach();
		std::cout<<S[i]<<std::endl;
	}
}
