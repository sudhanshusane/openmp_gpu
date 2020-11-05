#include <iostream>
#include <math.h>
#include <omp.h>
#include "TimingModule.h"

int main(int argc, char* argv[])
{

	std::cout << "Study testing the use of GPU via openmp" << std::endl;
	std::cout << "Number of CPU cores: " << omp_get_max_threads() << std::endl;
	std::cout << "Number of GPU cores: " << omp_get_num_devices() << std::endl;

	TimingModule *serial = new TimingModule();
	TimingModule *cpu = new TimingModule();
	TimingModule *gpu = new TimingModule();
	
// StartTimer(), EndTimer(), AccumulateTotalTime(), GetTotalTime()

	int n = atoi(argv[1]);		

	float *num = (float*)malloc(sizeof(float)*n);

	serial->StartTimer();
	for(int i = 0; i < n; i++)
	{
		num[i] = sqrt(pow(i,2.0) + pow(i, 3.0) + pow(i, 4.0)); 
		num[i] = sqrt(pow(i,2.0) + pow(i, 3.0) + pow(i, 4.0)); 
		num[i] = sqrt(pow(i,2.0) + pow(i, 3.0) + pow(i, 4.0)); 
	}
	serial->EndTimer();
	serial->AccumulateTotalTime();


	cpu->StartTimer();
	#pragma omp parallel for
	for(int i = 0; i < n; i++)
	{
		num[i] = sqrt(pow(i,2.0) + pow(i, 3.0) + pow(i, 4.0)); 
		num[i] = sqrt(pow(i,2.0) + pow(i, 3.0) + pow(i, 4.0)); 
		num[i] = sqrt(pow(i,2.0) + pow(i, 3.0) + pow(i, 4.0)); 
	}
	cpu->EndTimer();
	cpu->AccumulateTotalTime();
	
	gpu->StartTimer();
	#pragma omp target teams distribute parallel for
	for(int i = 0; i < n; i++)
	{
		num[i] = sqrt(pow(i,2.0) + pow(i, 3.0) + pow(i, 4.0)); 
		num[i] = sqrt(pow(i,2.0) + pow(i, 3.0) + pow(i, 4.0)); 
		num[i] = sqrt(pow(i,2.0) + pow(i, 3.0) + pow(i, 4.0)); 
	}
	gpu->EndTimer();
	gpu->AccumulateTotalTime();



	std::cout << "Serial time: " << serial->GetTotalTime() << std::endl; 
	std::cout << "CPU time: " << cpu->GetTotalTime() << std::endl; 
	std::cout << "GPU time: " << gpu->GetTotalTime() << std::endl; 
}
