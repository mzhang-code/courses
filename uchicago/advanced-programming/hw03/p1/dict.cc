
#include <cstring> 
#include <vector> 
#include "dict.h" 

using namespace std; 

bool flag[N]; 
pair<key_t, val_t> table[N]; 

unsigned int hashcode(key_t key) { 
	unsigned int sum = 0; 
	for (int i = 0; i < strlen(key.val); i++) { 
		sum += key.val[i]; 
	}
	return sum % N; 
}

val_t* find(key_t key) { 
	unsigned int code = hashcode(key); 
	unsigned int t = 1; 
	unsigned int k = code; 

	while (flag[k]) { 
		if (table[k].first == key) { 
			return &(table[k].second); 
		}
		k = (code + t*t) % N; 
		t++; 
	}
	return NULL; 
}

bool insert(key_t key, val_t val) { 
	unsigned int code = hashcode(key); 
	unsigned int t = 1; 
	unsigned int k = code; 

	while (flag[k]) { 
		if (table[k].first == key) { 
			return false; 
		}
		k = (code + t*t) % N; 
		t++; 
	}
	table[k] = {key, val}; 
	flag[k] = true; 
	return true; 
}

val_t* remove(key_t key) { 
	unsigned int code = hashcode(key); 
	unsigned int t = 1; 
	unsigned int k = code; 

	while (flag[k]) { 
		if (table[k].first == key) { 
			flag[k] = false; 
			return &(table[k].second); 
		}
		k = (code + t*t) % N; 
		t++; 
	}
	return NULL; 
}

void print() { 
	vector<key_t> lst; 
	lst.clear(); 
	for (int i = 0; i < N; i++) { 
		if (flag[i]) { 
			lst.push_back(table[i].first); 
		}
	}
	sort(lst.begin(), lst.end(), 
			[&] (const key_t &a, const key_t &b) -> bool {
				return strcmp(a.val, b.val) < 0;
			}); 
	for (key_t key : lst) { 
		printf("%s\n", key.val); 
	}
	return; 
}
