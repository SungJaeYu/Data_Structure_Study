#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  long long key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(long long key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool isBST_recursive(const vector<Node>& tree, int index, long long min, long long max){
	if (index == -1)
		return true;
	if (tree[index].key < min || tree[index].key > max)
		return false;
	return isBST_recursive(tree, tree[index].left, min, tree[index].key-1) && 
		isBST_recursive(tree, tree[index].right, tree[index].key, max);
}

bool IsBinarySearchTree(const vector<Node>& tree) {
	  if(tree.size() <= 1)
		  return true;
    return isBST_recursive(tree, 0, LLONG_MIN, LLONG_MAX);
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
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
