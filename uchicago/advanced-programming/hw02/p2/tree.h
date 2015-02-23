
#define N 100 
#define M 500 

struct key_t { 
	char val[N]; 

	key_t() {
		strcpy(this->val, "IGNORE"); 
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

struct obj_t { 
	char val[M]; 

	obj_t(char* val) { 
		strcpy(this->val, val); 
	}
}; 

struct tree_node_t { 
	void *left; 
	tree_node_t *right; 
	key_t key; 
}; 


tree_node_t* create_tree(void); 

obj_t* find(tree_node_t *root, key_t query); 

bool insert(tree_node_t *root, key_t key, obj_t *obj); 

obj_t* remove(tree_node_t *root, key_t key); 

void print(tree_node_t *root); 

