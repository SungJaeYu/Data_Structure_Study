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

//index 번째 vertex를 찾는 함수(index 1부터 시작)
Vertex* find(Vertex*& root, int index) {
  Vertex* v = root;
  Vertex* last = root;
  while(v != NULL){
    int s = (v->left != NULL)? v->left->size: 0;
    last = v;
    if(index == s + 1){
      break;
    }
    if(index < s + 1){
      v = v->left;
    }
    else if(index > s + 1){
      v = v->right;
      index = index - s - 1;
    }
  }
  splay(root, last);
  return last;
}

void split(Vertex* root, int index, Vertex*& left, Vertex*& right) {
  right = find(root, index);
  splay(root, right);
  if(right == NULL){
	  left = root;
	  return;
  }
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

char pop(int index) {                   
  Vertex* del_vertex = find(root, index);
  char cc = del_vertex->key;
  Vertex* left = del_vertex->left;
  Vertex* right = del_vertex->right;
  if(right == NULL){
	  root = left;
    if(root)
	    root->parent = NULL;
  }
  else if(left == NULL){
    root = right;
    if(root)
      root->parent = NULL;
  }
  else{
    left->parent = NULL;
    root->left = NULL;
    root = root->right;
    root->parent = NULL;

    find(root, 1);
    root->left = left;
    left->parent = root;
  }
  delete del_vertex;
  if(root)
    update(root);
  return cc;
}

class Rope {
  std::string result_str;
  std::string s;
public:
	Rope(std::string &s) : s(s){
		for(char &c : s){
			push(c);
		}
	}
	void process( int i, int j, int k ) {
		std::string subs;
		int len = j - i + 1;
		for(int ind = 0; ind < len; ind++){
      char pop_char = pop(i+1);
			subs.push_back(pop_char);
    }
		for(int ind = 0; ind < len; ind++)
			insert(k+ind, subs[ind]);
	}

  void process2(int i, int j, int k){
      std::string t = s.substr(0, i) + s.substr(j + 1);
      s = t.substr(0, k) + s.substr(i, j - i + 1) + t.substr(k);
  }
  
  std::string result(){
    result_str.clear();
    result_recur(root);
    return result_str;
  }

  std::string result2(){
    return s;
  }

	void result_recur(Vertex* v) {
		if(v == NULL)
			return;
		result_recur(v->left);
		result_str.push_back(v->key);
		result_recur(v->right);
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
    std::string test = rope.result();
    std::string test2 = rope.result2(); 
    if(!test.compare(test2)){
      std::cout << test << std::endl;
      std::cout<< test2 << std::endl;
    }
  }
	std::cout << rope.result() << std::endl;
}
