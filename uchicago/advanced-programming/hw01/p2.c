#include <stdio.h> 
#include <stdlib.h> 

#define SIG_BIT 31 
#define EXP_BIT 23

/* Program that prints the bit pattern of a float.
 */ 

void print_usage(char* argv[]) { 
	printf("P1 Usage: \n"); 
	printf("\t %s fpnum \n", argv[0]); 
}

int main(int argc, char* argv[]) { 
	if (argc < 2) { 
		print_usage(argv); 
	}
	float f = atof(argv[1]); 
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
