
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
#include <assert.h> 
#include <time.h> 

#include <sys/time.h>

#include <curand_kernel.h> 

#define D 5

#define TRIALS_PER_THREAD 2048
#define BLOCKS 256
#define THREADS 256 

__global__ void mc_int(double *res, curandState *states) { 
	unsigned int tid = threadIdx.x + blockDim.x*blockIdx.x;
	double integral = 0.0; 
	double X[D]; 

	curand_init(tid, 0, 0, &states[tid]); 
	for (int i = 0; i < TRIALS_PER_THREAD; i++) { 
		for (int j = 0; j < D; j++) { 
			X[j] = curand_uniform(&states[tid]); 
		}
		double t = 0.0; 
		for (int j = 0; j < D; j++) { 
			t -= X[j] * X[j]; 
		}
		integral += exp(t) / TRIALS_PER_THREAD; 
	}
	res[tid] = integral; 
}

int main(int argc, char **argv) { 

	double host[BLOCKS * THREADS]; 
	double *dev; 
	curandState *states; 

	double integral = 0.0; 
	double vol = 1.0; 

	clock_t ts = clock(); 
	struct timeval start, end;
	gettimeofday(&start, NULL);

	cudaMalloc((void**) &dev, BLOCKS * THREADS * sizeof(double));
	cudaMalloc((void**)&states, 
			BLOCKS * THREADS * sizeof(curandState));

	mc_int<<<BLOCKS, THREADS>>>(dev, states); 	

	cudaMemcpy(host, dev, BLOCKS * THREADS * sizeof(double), 
			cudaMemcpyDeviceToHost); 

	for(int i = 0; i < BLOCKS * THREADS; i++) {
		integral += host[i];
	}
	integral /= BLOCKS * THREADS;

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
	cudaFree(states);
}
