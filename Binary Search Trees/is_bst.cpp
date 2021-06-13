#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool IsBinarySearchTree(const vector<Node>& tree, int index) {
  // Implement correct algorithm here
  if(tree.size() == 0)
	  return true;

  static int prev_index = -1;

  if(index != -1)
  {
	  if(!IsBinarySearchTree(tree, tree[index].left))
		  return false;
	  if(prev_index != -1 && tree[index].key < tree[prev_index].key)
		  return false;
	  prev_index = index;

	  return IsBinarySearchTree(tree, tree[index].right);
  }
  return true;
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree, 0)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
