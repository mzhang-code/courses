
#include <cstdio> 
#include <ctime>
#include <cstdlib>

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
				C[i][j] = C[i][j] + A[i][k]*B[k][j]; 
			}
		}
	}
	return; 
}

void block_mmx(double **A, double **B, double **C, int n, int bs) { 
	return; 
}

void recursive_mmx(double **A, double **B, double **C, int n, int bs) { 
	return; 
}

int main() { 
	
	return 0; 
}
