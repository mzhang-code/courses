#include <stdio.h> 
#include <stdlib.h> 

void print_usage() { 
	printf("Usage \n"); 
	printf("p4 number \n"); 
	return; 
}

double **dmatrix(size_t m, size_t n) { 
	double **mat = malloc(sizeof(double*) * m); 
	for (int i = 0; i < m; i++) { 
		mat[i] = malloc(sizeof(double) * n); 
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

	for (int i = 0; i < n; i++) { 
		for (int j = 0; j < n; j++) { 
			if (j != 0) { 
				printf(" "); 
			}
			printf("%.1f", mat[i][j]); 
		}
		printf("\n"); 
	}

	for(int i = 0; i < n; i++) { 
		free(mat[i]); 
	}
	free(mat); 

	return 0; 
}
