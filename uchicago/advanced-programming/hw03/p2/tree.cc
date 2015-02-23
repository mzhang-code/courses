
#include <cstdio>
#include <cstring> 

#include "tree.h" 

using namespace std; 

void right_rotate(tree_node_ptr &root) { 
	tree_node_ptr l = root->left; 
	root->left = l->right; 
	l->right = root; 
	root = l; 	
}

void left_rotate(tree_node_ptr &root) { 
	tree_node_ptr r = root->right; 
	root->right = r->left; 
	r->left = root; 
	root = r; 
}

void left_balance(tree_node_ptr &root) { 
	tree_node_ptr l = root->left; 
	if (l->bal_fac == LH) { 
		root->bal_fac = EQ; 
		l->bal_fac = EQ; 
		right_rotate(root); 
	}
	else if (l->bal_fac == RH) { 
		tree_node_ptr lr = l->right; 
		if (lr->bal_fac == LH) { 
			root->bal_fac = RH; 
			l->bal_fac = EQ; 
		}
		else if (lr->bal_fac == EQ) { 
			root->bal_fac = EQ; 
			l->bal_fac = EQ; 
		}
		else if (lr->bal_fac == RH) { 
			root->bal_fac = EQ; 
			l->bal_fac = LH; 
		}
		lr->bal_fac = EQ; 
		left_rotate(root->left); 
		right_rotate(root); 
	}
}

void right_balance(tree_node_ptr &root) { 
	tree_node_ptr r = root->right; 
	if (r->bal_fac == RH) { 
		root->bal_fac = EQ; 
		r->bal_fac = EQ; 
	}
	else if (r->bal_fac == LH) { 
		tree_node_ptr rl = r->left; 
		if (rl->bal_fac == RH) { 

		}
		else if (rl->bal_fac == EQ) { 
			root->bal_fac = EQ; 
			r->bal_fac = EQ; 
		}
		else if (rl->bal_fac == LH) { 
			root->bal_fac = EQ; 
			r->bal_fac = RH; 
		}
		rl->bal_fac = EQ; 
		right_rotate(root->right); 
		left_rotate(root); 
	}
}

bool insert_avl(tree_node_ptr &root, key_t key, val_t val, bool &inc) { 
	if (!root) { 
		root = new tree_node_t(key, val); 
		inc = true; 
	}
	else { 
		if (root->key == key) { 
			inc = false; 
			return false; 
		}
		else if (key < root->key) { 
			if (!insert_avl(root->left, key, val, inc)) { 
				return false; 
			}
			if (inc) { 
				if (root->bal_fac == LH) { 
					left_balance(root); 
					inc = false; 
				}
				else if (root->bal_fac == EQ) { 
					root->bal_fac = LH; 
					inc = true; 
				}
				else if (root->bal_fac == RH) { 
					root->bal_fac = EQ; 
					inc = false; 
				}
			}
		}
		else { 
			if (!insert_avl(root->right, key, val, inc)) { 
				return false; 
			}
			if (inc) { 
				if (root->bal_fac == RH) {
					right_balance(root); 
				}
				if (root->bal_fac == EQ) { 
					root->bal_fac = RH; 
					inc = true; 
				}
				if (root->bal_fac == LH) { 
					root->bal_fac = EQ; 
					inc = false; 
				}
			}
		}
	}
	return true; 
}

val_t* find(tree_node_t *root, key_t query) { 
	if (!root) { 
		return NULL; 
	}
	if (root->key == query) { 
		return &(root->val); 
	}
	if (query < root->key) { 
		return find(root->left, query); 
	}
	return find(root->right, query); 
}

bool insert(tree_node_t *root, key_t key, val_t val) { 
	while (true) { 
		if (root->key == key) { 
			return false; 
		}
		else if (key < root->key) { 
			if (!root->left) { 
				root->left = new tree_node_t(key, val); 
				return true; 
			}
			root = root->left; 
		}
		else { 
			if (!root->right) { 
				root->right = new tree_node_t(key, val); 
				return true; 
			}
			root = root->right; 
		}
	}
}

// val_t remove(tree_node_t *root, key_t key) { 
// 	return; 	
// }

void preorder_print(tree_node_t *root) { 

	printf("[%s] -> '%s'\n", root->key.val, root->val.val); 

	if (root->left != NULL) { 
		preorder_print(root->left); 
	}
	if (root->right != NULL) { 
		preorder_print(root->right); 
	}
}

