#include <stdio.h> 
#include <stdlib.h> 

void print_usage() { 
	printf("Usage \n"); 
	printf("p5 number \n"); 
	return; 
}

double **dmatrix(size_t m, size_t n) { 
	double *nums = malloc(sizeof(double) * n * m); 
	double **mat = malloc(sizeof(double*) * m); 
	for (int i = 0; i < m; i++) { 
		mat[i] = nums + (n * i); 
	}
	return mat; 
}

int main(int argc, char *argv[]) { 
	if (argc != 2) { 
		print_usage(); 
		exit(1); 
	}
	int n = atoi(argv[1]); 
	double **mat = dmatrix(n, n); 

	int cnt = 0; 
	for (int i = 0; i < n; i++) { 
		for (int j = 0; j < n; j++) { 
			mat[i][j] = cnt++; 
		}
	}

	printf("Matrix with 1D indexing:\n"); 
	for (int i = 0; i < n * n; i++) { 
		printf("%.1f ", mat[0][i]); 
		if ((i+1) % n == 0) { 
			printf("\n"); 
		}
	}

	printf("\nMatrix with 2D indexing:\n"); 
	for (int i = 0; i < n; i++) { 
		for (int j = 0; j < n; j++) { 
			if (j != 0) { 
				printf(" "); 
			}
			printf("%.1f", mat[i][j]); 
		}
		printf("\n"); 
	}

	free(mat[0]); 
	free(mat); 

	return 0; 
}

