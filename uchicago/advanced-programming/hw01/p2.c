#include <stdio.h> 

#define SIG_BIT 31 
#define EXP_BIT 23

/* Program that prints the bit pattern of a float.
 * TODO: max and min. 
 */ 
int main() { 
	float f = 0.0; 
	scanf("%f", &f); 
	int mask = 0x1; 
	for (int i = sizeof(float) * 8 - 1; i >= 0; i--) { 
		printf("%d", ((*(int*)&f) >> i) & mask); 
		if (i == SIG_BIT || i == EXP_BIT) { 
			printf(" "); 
		}
	}
	printf("\n"); 
	return 0; 
}
