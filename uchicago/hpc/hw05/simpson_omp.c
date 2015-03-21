
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

int main(int argc, char **argv) { 
	double a = 0.0;
	double b = 1.0; 
	
	assert (argc == 2);
	int n = atoi(argv[1]); 

	double delta = (b-a) / n; 
	double integral = 0.0; 
	double h = delta / 2.0; 

	double w[3]; 
	w[0] = h / 3.0; 
	w[1] = 4.0 * w[0]; 
	w[2] = w[0]; 

	clock_t ts = clock(); 
	struct timeval start, end;
	gettimeofday(&start, NULL);

    omp_set_num_threads(THREAD_NUM); 

    #pragma omp parallel for shared(integral) 
	for (int i5 = 0; i5 < n; i5++) { 
	for (int j5 = 0; j5 < 3; j5++) { 
		double x5 = a + i5 * delta + j5 * h; 
		for (int i4 = 0; i4 < n; i4++) { 
		for (int j4 = 0; j4 < 3; j4++) { 
			double x4 = a + i4 * delta + j4 * h; 
			for (int i3 = 0; i3 < n; i3++) { 
			for (int j3 = 0; j3 < 3; j3++) { 
				double x3 = a + i3 * delta + j3 * h; 
				for (int i2 = 0; i2 < n; i2++) { 
				for (int j2 = 0; j2 < 3; j2++) { 
					double x2 = a + i2 * delta + j2 * h; 
					for (int i1 = 0; i1 < n; i1++) { 
					for (int j1 = 0; j1 < 3; j1++) { 
						double x1 = a + i1 * delta + j1 * h; 
            			#pragma omp atomic
						integral += w[j1] * w[j2] * w[j3] * 
							w[j4] * w[j5] * f(x1, x2, x3, x4, x5); 
					}
					}
				}
				}
			}
			}
		}
		}
	}
	}

	gettimeofday(&end, NULL);
	double elapsed = ((end.tv_sec  - start.tv_sec) * 1000000u + 
			         end.tv_usec - start.tv_usec) / 1.e6;
	ts = clock() - ts; 

	printf("%ld clocks (%lf seconds)\n", ts, elapsed); 
	printf("integral is: %lf\n", integral);	

	return 0; 
}
