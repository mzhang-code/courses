
#include <cstdio>
#include <cstring> 

#include "tree.h" 

using namespace std; 

tree_node_t* create_tree(void) { 
	tree_node_t *root = new tree_node_t(); 
	root->left = NULL; 
	return root; 
}

obj_t* find(tree_node_t *root, key_t query) { 
	if ((root->left == NULL) || 
			(root->right == NULL && !(root->key == query))) { 
		return NULL; 
	}
	else if (root->right == NULL && 
			root->key == query) { 
		return (obj_t*)(root->left); 
	}
	else { 
		if (query < root->key) { 
			return find((tree_node_t*)(root->left), query); 
		}
		return find(root->right, query); 
	}
}

bool insert(tree_node_t *root, key_t key, obj_t *obj) { 
	if (root->left == NULL) { 
		root->left = (void*)obj; 
		root->key = key; 
		root->right = NULL; 
	}
	else { 
		tree_node_t *tmp = root; 
		while (tmp->right != NULL) { 
			if (key < tmp->key) { 
				tmp = (tree_node_t*)tmp->left; 
			}
			else { 
				tmp = tmp->right; 
			}
		}
		if (tmp->key == key) { 
			return false; 
		}
		tree_node_t *old_leaf, *new_leaf; 
		old_leaf = new tree_node_t(); 
		old_leaf->left = tmp->left; 
		old_leaf->key = tmp->key; 
		old_leaf->right = NULL; 
		new_leaf = new tree_node_t(); 
		new_leaf->left = (void*)obj; 
		new_leaf->key = key; 
		new_leaf->right = NULL; 
		
		if (tmp->key < key) { 
			tmp->left = old_leaf; 
			tmp->right = new_leaf; 
			tmp->key = key; 
		}
		else { 
			tmp->left = new_leaf; 
			tmp->right = old_leaf; 
		}
	}
	return true; 
}

obj_t* remove(tree_node_t *root, key_t key) { 
	tree_node_t *tmp, *upper, *other; 
	obj_t *obj; 

	if (root->left == NULL) { 
		return NULL; 
	}
	if (root->right == NULL) { 
		if (root->key == key) { 
			obj = (obj_t*)root->left; 
			root->left = NULL; 
			return obj; 
		}
		return NULL; 
	}
	else { 
		tmp = root; 
		while (tmp->right != NULL) { 
			upper = tmp; 
			if (key < tmp->key) { 
				tmp = (tree_node_t*)upper->left; 
				other = upper->right; 
			}
			else { 
				tmp = upper->right; 
				other = (tree_node_t*)upper->left; 
			}
		}
		if (!(tmp->key == key)) { 
			return NULL; 
		}
		else { 
			upper->key = other->key; 
			upper->left = other->left; 
			upper->right = other->right; 
			obj = (obj_t*)tmp->left; 
			delete(tmp); 
			delete(other); 
			return obj; 
		}
	}
}

void print(tree_node_t *root) { 
	if (root->left == NULL) { 
		return; 
	}
	if (root->right == NULL) { 
		printf("[%s] -> '%s'\n", root->key.val, ((obj_t*)root->left)->val); 
	}
	else { 
		print((tree_node_t*)root->left); 
		print(root->right); 
	}
}

