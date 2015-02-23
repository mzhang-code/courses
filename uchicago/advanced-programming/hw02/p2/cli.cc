
#include <cstdio> 
#include <cstring> 

#include "tree.h" 

using namespace std; 

#define CMD_LEN 10 
#define WORD_LEN 100 
#define DESC_LEN 500 
#define LINE_LEN 600

bool read_desc(char *buf, char *desc) { 
	int s = 0; 
	int t = 0; 
	int n = strlen(buf); 
	while (buf[s] != '"' && s < n) { 
		s++; 
	}
	if (s == n) { 
		return false; 
	}
	t = s + 1; 
	while (t < n && buf[t] != '"') { 
		t++;
	}
	if (t == n) { 
		return false; 
	}
	strncpy(desc, buf + s + 1, t - s - 1); 
	return true;
}

void print_usage() { 
	printf("For full instructions on cmd:\n");
	printf("\t> help\n");
}

void print_greet() { 
	printf("\nWord Dict using Model #1 binary tree\n");
	printf("Usage:\n");
	printf("\t$ ./dict\n");
	printf("\t> cmd [args]\n");
	printf("For full instructions on cmd:\n");
	printf("\t> help\n");
}

int main() { 

	print_greet(); 

	char line[LINE_LEN]; 
	char cmd[CMD_LEN]; 
	char word[WORD_LEN]; 
	char desc[DESC_LEN]; 

	tree_node_t *root = create_tree(); 

	while (1) { 
		printf("> "); 

		if(gets(line) == NULL) { 
			break; 
		}
		sscanf(line, "%s", cmd); 

		memset(desc, '\0', sizeof(word)); 
		memset(desc, '\0', sizeof(desc)); 
		if (strcmp("add", cmd) == 0) { 
			if (sscanf(line + strlen(cmd), "%s", word) == EOF) { 
				printf("[ERROR] no word\n"); 
				print_usage(); 
				continue; 
			}
			if (!read_desc(line + strlen(cmd) + strlen(word), desc)) { 
				printf("[ERROR] wrong format with description.\n"); 
				print_usage(); 
				continue; 
			}
			key_t key(word); 
			obj_t *obj = new obj_t(desc); 
			insert(root, key, obj); 
		}
		else if (strcmp("delete", cmd) == 0) { 
			if (sscanf(line + strlen(cmd), "%s", word) == EOF) { 
				printf("[ERROR] no word\n"); 
				print_usage(); 
				continue; 
			}
			
			key_t key(word); 
			obj_t *obj = remove(root, key); 
			if (obj) { 
				printf("Deleted [%s] -> '%s'\n", key.val, obj->val); 
				delete obj; 
			}
			else { 
				printf("There's no such key [%s]\n", key.val); 
			}
		}
		else if (strcmp("find", cmd) == 0) { 
			if (sscanf(line + strlen(cmd), "%s", word) == EOF) { 
				printf("[ERROR] no word\n"); 
				print_usage(); 
				continue; 
			}
			key_t key(word); 
			obj_t *obj = find(root, key); 
			if (obj) { 
				printf("'%s'\n", obj->val); 
			}
			else { 
				printf("There's no such key [%s]\n", key.val); 
			}
		}
		else if (strcmp("print", cmd) == 0) { 
			print(root); 
		}
		else if (strcmp("help", cmd) == 0) { 
			print_usage(); 
		}
		else { 
			printf("[ERROR] unknown cmd: %s\n", cmd); 
			print_usage(); 
		}

	}
	printf("\nBye for now!\n"); 
	return 0;
}
