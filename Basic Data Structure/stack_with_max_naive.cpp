#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

using std::cin;
using std::string;
using std::vector;
using std::cout;
using std::max_element;

class StackWithMax {
    vector<int> stack;
	vector<int> max_s;
  public:

    void Push(int value) {
        stack.push_back(value);
		if(max_s.empty())
			max_s.push_back(value);
		else
			max_s.push_back(std::max(max_s.back(), value));
    }

    void Pop() {
        assert(stack.size());
        stack.pop_back();
		max_s.pop_back();
    }

    int Max() const {
        assert(stack.size());
        return max_s.back();
    }
};

int main() {
    int num_queries = 0;
    cin >> num_queries;

    string query;
    string value;

    StackWithMax stack;

    for (int i = 0; i < num_queries; ++i) {
        cin >> query;
        if (query == "push") {
            cin >> value;
            stack.Push(std::stoi(value));
        }
        else if (query == "pop") {
            stack.Pop();
        }
        else if (query == "max") {
            cout << stack.Max() << "\n";
        }
        else {
            assert(0);
        }
    }
    return 0;
}
