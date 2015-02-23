#include <stdio.h> 
#include <stdlib.h> 

#define MAX_LINES 1000 
#define MAX_CHAR_PER_LINE 1000 

int main(int argc, char* argv[]) { 
	FILE* fp = fopen(argv[1], "r"); 
	if (!fp) { 
		printf("Error with open file."); 
		exit(1); 
	}
	char text[MAX_LINES][MAX_CHAR_PER_LINE]; 
	int nlines = 0; 
	size_t len = MAX_CHAR_PER_LINE; 
	while (1) { 
		char *line = text[nlines]; 
		if (getline(&line, &len, fp) == -1) { 
			break; 
		}
		nlines++; 
	}
	for (int i = 0; i < nlines; i++) { 
		printf("%s", text[i]); 
	}
	printf("\n"); 
	fclose(fp); 
	return 0; 
}
