
#include <utility> 

#define M 500
#define N 100000

using namespace std; 

struct key_t { 
	char val[N]; 

	key_t() {
	}
	key_t(char* val) { 
		strcpy(this->val, val); 
	}
	key_t& operator = (const key_t &rhs) { 
		strcpy(this->val, rhs.val); 
		return *this; 
	}
	bool operator < (const key_t &rhs) { 
		return strcmp(this->val, rhs.val) < 0; 
	}
	bool operator == (const key_t &rhs) { 
		return strcmp(this->val, rhs.val) == 0; 
	}
};

struct val_t { 
	char val[M]; 
	
	val_t& operator = (const val_t &rhs) { 
		strcpy(this->val, rhs.val); 
		return *this; 
	}
	val_t() { 
	}
	val_t(char* _val) { 
		strcpy(this->val, _val); 
	}
}; 


extern pair<key_t, val_t> table[N]; 
extern bool flag[N]; 

unsigned int hashcode(key_t key); 

val_t* find(key_t k); 

bool insert(key_t k, val_t v); 

val_t* remove(key_t k); 

void print(); 

