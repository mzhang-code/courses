
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
#include <assert.h> 
#include <time.h> 

#include <sys/time.h>

#include <omp.h>

#define THREAD_NUM 16

#define D 5

double f(double x1, double x2, double x3, double x4, double x5) { 
	return exp(-x1*x1 - x2*x2 - x3*x3 - x4*x4 - x5*x5);
}

double uran(double a, double b){
	return rand() / (RAND_MAX + 1.0) * (b - a) + a;
}

int main(int argc, char **argv) { 

	srand(time(0)); 

	double a = 0.0;
	double b = 1.0; 
	
	double X[D]; 
	double integral = 0.0; 
	double vol = 1.0; 

	assert (argc == 2);
	int n = atoi(argv[1]); 

	clock_t ts = clock(); 
	struct timeval start, end;
	gettimeofday(&start, NULL);

    omp_set_num_threads(THREAD_NUM); 

    #pragma omp parallel for shared(integral) 
	for (int i = 0; i < n; i++) { 
		for (int j = 0; j < D; j++) { 
			X[j] = uran(a, b); 
		}
		#pragma omp atomic
		integral += f(X[0], X[1], X[2], X[3], X[4]) / n; 
	}

	for (int j = 0; j < D; j++) { 
		vol *= b - a; 
	}
	integral *= vol; 

	gettimeofday(&end, NULL);
	double elapsed = ((end.tv_sec  - start.tv_sec) * 1000000u + 
			         end.tv_usec - start.tv_usec) / 1.e6;
	ts = clock() - ts; 

	printf("%ld clocks (%lf seconds)\n", ts, elapsed); 
	printf("integral is: %lf\n", integral);	
}
		
