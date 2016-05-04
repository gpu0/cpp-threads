#include<iostream>
#include<vector>
#include<thread>
#include<stdint.h>

class add{
public:
	int a, b, c;
	add(int a, int b) : a(a), b(b), c(c) {}
	void operator()()
	{
		c = a + b;
	}
};

class Saxpy{
public:
	float a, X, b, Y;
	float *S;
	Saxpy(float *S, float a, float X, float b, float Y) : a(a), X(X), b(b), Y(Y), S(S) {}
	void operator()(){
		*S = a*X + b*Y;
	}
};

int main()
{
	class add Add(1,2);
	Add();
	std::cout<<Add.c<<std::endl;

	uint32_t num_cpus = std::thread::hardware_concurrency();
	std::vector<std::thread>threads(num_cpus);

	float *S = new float[num_cpus], a = 1.0f, b = 2.0f, *X = new float[num_cpus], *Y = new float[num_cpus];

	for(uint32_t i=0;i<num_cpus;i++){
		X[i] = 1.0f*i;
		Y[i] = 2.0f*(i+1);
		Saxpy saxpy(S+i, a, X[i], b, Y[i]);
		threads[i] = std::thread(saxpy);
	}

	for(uint32_t i=0;i<num_cpus;i++){
		threads[i].join();
		std::cout<<S[i]<<std::endl;
	}
}
