#include <stdio.h>
#include <stdlib.h> 
  
void heapify(int *f, int n) {
	/* Your Code Here */
	for (int i = n-1; i > 0; i--) { 
		int p = i; 
		while (p > 0) { 
			if (f[p] > f[p/2]) { 
				int t = f[p]; 
				f[p] = f[p/2]; 
				f[p/2] = t; 
			}
			p = p/2; 
		}
	}
}

int * allocate_array( int argc, char * argv[]) {
	/* Your Code Here */
	int n = argc - 1; 
	int *p = malloc(n * sizeof(int)); 
	for (int i = 0; i < n; i++) { 
		*(p+i) = atoi(argv[i+1]); 
	}
	return p; 
}

int test_heap( int * f, int n) {
	int i;
	int child_A, child_B;

	for( i = 0; i < n; i++ ) {
		child_A = ( 2 * i ) + 1;
		child_B = ( 2 * i ) + 2;

		if( child_A < n )
			if( f[i] < f[child_A] )
				return -1;
		
		if( child_B < n )
			if( f[i] < f[child_B] )
				return -1;
	}

	return 1;
}

int main(int argc, char * argv[])
{
	int result;
	int i;
	int n = argc - 1;
	int * arr = allocate_array( argc, argv );

	heapify( arr, n );
	result = test_heap( arr, n );

	for( i = 0; i < n; i++ )
		printf("%d ", arr[i]);
	printf("\n");

	if( result == 1 )
		printf("Heap test success!\n");
	else
		printf("Heap test failed.\n");

	free(arr);

	return 0;
}

