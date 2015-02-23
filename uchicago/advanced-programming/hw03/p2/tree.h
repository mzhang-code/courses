
#define N 100 
#define M 500 

#define LH 1 
#define EQ 0 
#define RH -1 

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

struct tree_node_t { 
	tree_node_t *left, *right; 
	key_t key; 
	val_t val; 
	int bal_fac; 

	tree_node_t(key_t _key, val_t _val) { 
		key = key_t(_key); 
		val = val_t(_val); 
		left = NULL; 
		right = NULL; 
		bal_fac = EQ; 
	}
}; 

typedef tree_node_t* tree_node_ptr; 

val_t* find(tree_node_t *root, key_t query); 

bool insert(tree_node_t *root, key_t key, val_t val); 

bool insert_avl(tree_node_ptr &root, key_t key, val_t val, bool &inc); 

// val_t remove(tree_node_t *root, key_t key); 

void preorder_print(tree_node_t *root); 

