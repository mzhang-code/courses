#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#define N 10000
#define M 100

void swap(char **x, char **y) { 
	char *t = *x; 
	*x = *y; 
	*y = t; 
}

int partition(char **A, int s, int t) { 
	int i = s-1; 
	char *x = A[t-1]; 
	for (int j = s; j < t-1; j++) { 
		if (strcmp(A[j], x) < 0) { 
			swap(&A[++i], &A[j]); 
		}
	}
	swap(&A[++i], &A[t-1]); 
	return i; 
}

void str_qsort(char **A, int s, int t) { 
	if (s < t-1) { 
		int m = partition(A, s, t); 
		str_qsort(A, s, m); 
		str_qsort(A, m+1, t); 
	}
}

void alphabetize(char *text[], int nlines) { 
	str_qsort(text, 0, nlines); 
}

int main() { 
	int nlines = 0; 
	char **text; 
	text = malloc(N * sizeof(char*)); 
	for (int i = 0; i < N; i++) { 
		text[i] = malloc(M * sizeof(char)); 
	}
	size_t len = M; 
	char *line = NULL; 
	while (1) { 
		line = text[nlines]; 
		if (getline(&line, &len, stdin) == -1) { 
			break; 
		}
		nlines++; 
	}
	
	alphabetize(text, nlines); 

	for (int i = 0; i < nlines; i++) { 
		printf("%s", text[i]); 
		free(text[i]); 
	}
	free(text); 
	return 0; 
}
