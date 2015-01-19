#include <ctime>
#include <cstdio>
#include <cstdlib>

using namespace std; 

int main() { 
	int n = 1000000000; 
	double a = 1.0; 
	clock_t ts = clock(); 

	for (int i = 0; i < n; i++) { 
		a += 1.0;
	}

	ts = clock() - ts; 
	printf("%d clocks (%f seconds)\n", ts, ((float)ts)/CLOCKS_PER_SEC); 
	return 0;
}

