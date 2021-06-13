#include <cstdio>
#include <string>
#include <iostream>

struct Vertex {
  char key;
  // Sum of all the keys in the subtree - remember to update
  // it after each operation that changes the tree.
  int size;
  Vertex* left;
  Vertex* right;
  Vertex* parent;

  Vertex(char key, int size, Vertex* left, Vertex* right, Vertex* parent) 
  : key(key), size(size), left(left), right(right), parent(parent) {}
};

void update(Vertex* v) {
  if (v == NULL) return;
  v->size = (v->left != NULL ? v->left->size : 0) + (v->right != NULL ? v->right->size : 0) + 1;
  if (v->left != NULL) {
    v->left->parent = v;
  }
  if (v->right != NULL) {
    v->right->parent = v;
  }
}

void small_rotation(Vertex* v) {
  Vertex* parent = v->parent;
  if (parent == NULL) {
    return;
  }
  Vertex* grandparent = v->parent->parent;
  if (parent->left == v) {
    Vertex* m = v->right;
    v->right = parent;
    parent->left = m;
  } else {
    Vertex* m = v->left;
    v->left = parent;
    parent->right = m;
  }
  update(parent);
  update(v);
  v->parent = grandparent;
  if (grandparent != NULL) {
    if (grandparent->left == parent) {
      grandparent->left = v;
    } else {
      grandparent->right = v;
    }
  }
}

void big_rotation(Vertex* v) {
  if (v->parent->left == v && v->parent->parent->left == v->parent) {
    // Zig-zig
    small_rotation(v->parent);
    small_rotation(v);
  } else if (v->parent->right == v && v->parent->parent->right == v->parent) {
    // Zig-zig
    small_rotation(v->parent);
    small_rotation(v);
  } else {
    // Zig-zag
    small_rotation(v);
    small_rotation(v);
  }  
}

// Makes splay of the given vertex and makes
// it the new root.
void splay(Vertex*& root, Vertex* v) {
  if (v == NULL) return;
  while (v->parent != NULL) {
    if (v->parent->parent == NULL) {
      small_rotation(v);
      break;
    }
    big_rotation(v);
  }
  root = v;
}

// Searches for the given key in the tree with the given root
// and calls splay for the deepest visited node after that.
// If found, returns a pointer to the node with the given key.
// Otherwise, returns a pointer to the node with the smallest
// bigger key (next value in the order).
// If the key is bigger than all keys in the tree, 
// returns NULL.
Vertex* find(Vertex*& root, Vertex* v, int index) {
  if(root->size < index)
	  return NULL;
  int s = (v->left != NULL)? v->left->size: 0;
  if(index == s + 1){
	  splay(root, v);
	  return v;
  }
  if(index < s + 1) return find(root, v->left, index);
  if(index > s + 1) return find(root, v->right, index - s - 1);
  return NULL;
}

void split(Vertex* root, int index, Vertex*& left, Vertex*& right) {
  right = find(root, root, index);
  if(right == NULL){
	  left = root;
	  return;
  }
  splay(root, right);
  left = right->left;
  right->left = NULL;
  if (left != NULL) {
    left->parent = NULL;
  }
  update(left);
  update(right);
}

Vertex* merge(Vertex* left, Vertex* right) {
  if (left == NULL) return right;
  if (right == NULL) return left;
  Vertex* min_right = right;
  while (min_right->left != NULL) {
    min_right = min_right->left;
  }
  splay(right, min_right);
  right->left = left;
  update(right);
  return right;
}

// Code that uses splay tree to solve the problem

Vertex* root = NULL;

void insert(int index, char c) {
  Vertex* left = NULL;
  Vertex* right = NULL;
  Vertex* new_vertex = NULL;  
  split(root, index+1, left, right);
  new_vertex = new Vertex(c, 1, NULL, NULL, NULL);
  root = merge(merge(left, new_vertex), right);
}

void push(char c) {
	Vertex* new_vertex = new Vertex(c, 1, NULL, NULL, NULL);
	root = merge(root, new_vertex);
}

char erase(int index) {
  // Implement erase yourself
  find(root, root, index+1);
  Vertex* del_vertex = find(root, root, index);
  char del_char = del_vertex->key;
  Vertex* left = del_vertex->left;
  Vertex* right = del_vertex->right;
  delete del_vertex;
  if(right == NULL){
	  root = left;
	  root->parent = NULL;
	  return del_char;
  }
  if(left == NULL){
	  root = right;
	  root->parent = NULL;
	  return del_char;
  }
  right->left = left;
  left->parent = right;
  root = right;
  root->parent = NULL;
  update(root);
  return del_char;
}


class Rope {
public:
	Rope(std::string &s){
		for(char &c : s){
			push(c);
		}
	}

	void process( int i, int j, int k ) {
		std::string subs;
		int len = j - i + 1;
		for(int ind = 0; ind < len; ind++)
			subs.push_back(erase(i+1));
		for(int ind = 0; ind < len; ind++)
			insert(k+ind, subs[ind]);
	}

	void result(Vertex* v) {
		if(v == NULL)
			return;
		result(v->left);
		std::cout << v->key;
		result(v->right);
	}
};

int main() {
	std::ios_base::sync_with_stdio(0);
	std::string s;
	std::cin >> s;
	Rope rope(s);
	int actions;
	std::cin >> actions;
        for (int action_index = 0; action_index < actions; ++action_index) {
                int i, j, k;
		std::cin >> i >> j >> k;
		rope.process(i, j, k);
		rope.result(root);
	}
	rope.result(root);
	std::cout << std::endl;
}
