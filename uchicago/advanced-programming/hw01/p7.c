#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <unistd.h> 

#define M 1000 
#define N 1000 

double **dmatrix_1d(size_t m, size_t n) { 
	double *nums = malloc(sizeof(double) * n * m); 
	double **mat = malloc(sizeof(double*) * m); 
	for (int i = 0; i < m; i++) { 
		mat[i] = nums + (n * i); 
	}
	return mat; 
}

double **dmatrix_2d(size_t m, size_t n) { 
	double **mat = malloc(sizeof(double*) * m); 
	for (int i = 0; i < m; i++) { 
		mat[i] = malloc(sizeof(double) * n); 
	}
	return mat; 
}

void work_kernel_dynamic(double **U, int m, int n)
{
	int i,j;
	double a = 1.0, b = 0.5, c;

	for( i=1; i < (m-1); i++)
		for( j=1; j < (n-1); j++)
		{
			c = ( a * (U[i+1][j] + U[i-1][j]) ) +
		            ( b * (U[i][j+1] + U[i][j-1]) ) +
	                    ( (1 - (2*a) - (2*b)) * U[i][j] );
		}

	return;
}

void work_kernel_static(double U[M][N], int m, int n)
{
	int i,j;
	double a = 1.0, b = 0.5, c;

	for( i=1; i < (m-1); i++)
		for( j=1; j < (n-1); j++)
		{
			c = ( a * (U[i+1][j] + U[i-1][j]) ) +
		            ( b * (U[i][j+1] + U[i][j-1]) ) +
	                    ( (1 - (2*a) - (2*b)) * U[i][j] );
		}

	return;
}



int main(int argc, char * argv[])
{
	
	int m = M;
	int n = N;

	/* Declare and allocate your arrays A,B,C */
	double A[M][N]; 
	double **B; 
	double **C; 
	/* Initialize arrays */
	B = dmatrix_2d(m, n); 
	C = dmatrix_1d(m, n); 

	for (int i = 0; i < m; i++) { 
		for (int j = 0; j < n; j++) { 
			A[i][j] = i*n + j; 
			B[i][j] = i*n + j; 
			C[i][j] = i*n + j; 
		}
	}
	clock_t start; 

	/* time A */
	start = clock(); 
	work_kernel_static(A, m, n);
	printf("%lu\n", clock() - start); 

	/* time B */
	start = clock(); 
	work_kernel_dynamic( B, m, n);
	printf("%lu\n", clock() - start); 

	/* time C */
	start = clock(); 
	work_kernel_dynamic( C, m, n);
	printf("%lu\n", clock() - start); 

	
	/* Print out timing to stdout in seconds for each array */
	/* Free memory*/
		
	return 0;

}
