#include <stdio.h> 
#include <stdlib.h> 

double ***d3arr(size_t l, size_t m, size_t n) { 
	double *nums = malloc(sizeof(double) * l * m * n); 
	double **mat = malloc(sizeof(double*) * l * m); 
	double ***mat3 = malloc(sizeof(double**) * l); 

	for (int i = 0; i < l * m; i++) { 
		mat[i] = nums + (n * i); 
	}
	for (int i = 0; i < l; i++) { 
		mat3[i] = mat + (m * i); 
	}
	return mat3; 
}

int main(int argc, char* argv[]) { 
	int n = atoi(argv[1]); 
	double ***mat3 = d3arr(n, n, n); 
	int cnt = 0; 
	for (int i = 0; i < n; i++) { 
		for (int j = 0; j < n; j++) { 
			for (int k = 0; k < n; k++) { 
				mat3[i][j][k] = cnt++; 
			}
		}
	}

	printf("Matrix with 1D indexing:\n"); 
	for (int i = 0; i < n * n * n; i++) { 
		printf("%d ", (int)mat3[0][0][i]); 
		if ((i+1) % n == 0) { 
			printf("\n"); 
		}
		if ((i+1) % (n*n) == 0) { 
			printf("\n"); 
		}
	}

	printf("Matrix with 3D indexing:\n"); 
	for (int i = 0; i < n; i++) { 
		for (int j = 0; j < n; j++) { 
			for (int k = 0; k < n; k++) { 
				printf("%d ", (int)mat3[i][j][k]); 
			}
			printf("\n"); 
		}
		printf("\n"); 
	}

	return 0; 
}

