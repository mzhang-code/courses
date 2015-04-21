
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
#include <assert.h> 
#include <time.h> 

#include <sys/time.h>

#include <curand_kernel.h> 

#define D 5

#define BLOCKS 125
#define THREADS 25
#define N 5

__global__ void simpson_int(double *res) { 
	unsigned int tid = threadIdx.x + blockDim.x*blockIdx.x;
	int t = tid; 
	double integral = 0.0; 
	double X[D]; 

	X[0] = t % N; t /= N; 
	X[1] = t % N; t /= N; 
	X[2] = t % N; t /= N; 
	X[3] = t % N; t /= N; 
	X[4] = t % N; 
	
	double T = 0.0; 
	for (int j = 0; j < D; j++) { 
		X[j] = X[j] / N; 
		T -= X[j] * X[j]; 
	}
	integral += exp(T) * pow(1.0/N, 5.0);
	res[tid] = integral; 
}

int main(int argc, char **argv) { 

	double host[BLOCKS * THREADS]; 
	double *dev; 

	double integral = 0.0; 
	double vol = 1.0; 

	clock_t ts = clock(); 
	struct timeval start, end;
	gettimeofday(&start, NULL);

	cudaMalloc((void**) &dev, BLOCKS * THREADS * sizeof(double));

	simpson_int<<<BLOCKS, THREADS>>>(dev); 	

	cudaMemcpy(host, dev, BLOCKS * THREADS * sizeof(double), 
			cudaMemcpyDeviceToHost); 

	for(int i = 0; i < BLOCKS * THREADS; i++) {
		integral += host[i];
	}

	for (int j = 0; j < D; j++) { 
		vol *= 1.0; 
	}
	integral *= vol; 

	gettimeofday(&end, NULL);
	double elapsed = ((end.tv_sec  - start.tv_sec) * 1000000u + 
			         end.tv_usec - start.tv_usec) / 1.e6;
	ts = clock() - ts; 

	printf("%ld clocks (%lf seconds)\n", ts, elapsed); 
	printf("integral is: %lf\n", integral);	
	cudaFree(dev);
}
