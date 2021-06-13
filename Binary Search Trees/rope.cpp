#include <cstdio>
#include <string>
#include <iostream>


// Replace this code with a faster implementation
class Rope {
	std::string s;
public:
	Rope(const std::string &s) : s(s) { 
	}

	void process( int i, int j, int k ) {
		
	}

	std::string result() {
		return s;
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
	}
	std::cout << rope.result() << std::endl;
}
