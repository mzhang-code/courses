
#include <stdio.h> 

#define BYTE_SIZE 8

/* Takes a single integer as input and flips its endianness.
 * Bitshifting and the bitwise operators need to be involved. 
 */ 
int flip_endian(int x) { 
	int rtn = 0; 
	int mask = (0x1 << BYTE_SIZE) - 1; 
	for (int i = 0; i < sizeof(int); i++) { 
		rtn = rtn << BYTE_SIZE; 
		rtn += x & mask; 
		x = x >> BYTE_SIZE; 
	}
	return rtn; 
}

int main() { 
	int n = 0; 
	scanf("%d", &n); 
	printf("%d\n", flip_endian(n)); 
	return 0; 
}

