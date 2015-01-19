
#include <cstdio> 
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <algorithm> 

using namespace std; 

double** create_mat(int n) { 
	double **A = new double*[n];
	for (int i = 0; i < n; i++) {
		A[i] = new double[n];
		for (int j = 0; j < n; j++) { 
			A[i][j] = 0.0;
		}	
	}
	return A; 
}

void rand_mat(double **A, int n) { 
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			A[i][j] = (double)(rand() % 1000);
		}
	}
	return; 
}

void naive_mmx(double **A, double **B, double **C, int n, int bs) { 
	for (int i = 0; i < n; i++) { 
		for (int j = 0; j < n; j++) { 
			for (int k = 0; k < n; k++) { 
				C[i][j] += A[i][k] * B[k][j]; 
			}
		}
	}
	return; 
}

void block_mmx(double **A, double **B, double **C, int n, int bs) { 
	for (int bj = 0; bj < n; bj += bs) { 
		for (int bk = 0; bk < n; bk += bs) { 
			for (int i = 0; i < n; i++) { 
				for (int j = bj; j < min(bj+bs, n); j++) { 
					for (int k = bk; k < min(bk+bs, n); k++) { 
						C[i][j] += A[i][k] * B[k][j]; 
					}
				}
			}
		}
	}
	return; 
}

void rmm_internal(double **A, int ra, int ca, double **B, int rb, int cb, 
		double **C, int rc, int cc, int n) { 
	if (n == 1) { 
		C[rc][cc] += A[ra][ca] * B[rb][cb]; 
	}
	else { 
		rmm_internal(A, ra, ca, B, rb, cb, C, rc, cc, n/2); 
		rmm_internal(A, ra, ca + n/2, B, rb + n/2, cb, C, rc, cc, n/2); 

		rmm_internal(A, ra, ca, B, rb, cb + n/2, C, rc, cc + n/2, n/2); 
		rmm_internal(A, ra, ca + n/2, B, rb + n/2, cb + n/2, 
				C, rc, cc + n/2, n/2); 

		rmm_internal(A, ra + n/2, ca, B, rb, cb, C, rc + n/2, cc, n/2); 
		rmm_internal(A, ra + n/2, ca + n/2, B, rb + n/2, cb, 
				C, rc + n/2, cc, n/2); 

		rmm_internal(A, ra + n/2, ca, B, rb, cb + n/2, 
				C, rc + n/2, cc + n/2, n/2); 
		rmm_internal(A, ra + n/2, ca + n/2, B, rb + n/2, cb + n/2, 
				C, rc + n/2, cc + n/2, n/2); 

	}
}

void recursive_mmx(double **A, double **B, double **C, int n, int bs) { 
	rmm_internal(A, 0, 0, B, 0, 0, C, 0, 0, n); 
}

int main(int argc, char **argv) { 
	
	int c; 
	int t = 0; 
	int n = 0; 
	int b = 0;
	while ((c = getopt(argc, argv, "t:n:b:")) != -1) { 
		switch (c) { 
			case 't':
				t = atoi(optarg); 
				break;
			case 'n': 
				n = atoi(optarg); 
				break; 
			case 'b': 
				b = atoi(optarg); 
				break; 
		}
	}
	// printf("%d %d %d\n", t, n, b); 
	
	double **A = create_mat(n);
	double **B = create_mat(n);
	double **C = create_mat(n);

	rand_mat(A, n);
	rand_mat(B, n);

	clock_t ts = clock(); 
	if (t == 0) { 
		printf("naive matrix multiply %d\n", n); 
		naive_mmx(A, B, C, n, b); 
	}
	else if (t == 1) { 
		printf("block matrix multiply %d %d\n", n, b); 
		block_mmx(A, B, C, n, b); 
	}
	else {
		printf("recursive matrix multiply %d\n", n); 
		recursive_mmx(A, B, C, n, b); 
	}
	ts = clock() - ts; 
	printf("%d clocks (%f seconds)\n", ts, ((float)ts)/CLOCKS_PER_SEC); 

	return 0; 
}
