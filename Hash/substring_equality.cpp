#include <iostream>

using namespace std;

class Solver {
	string s;
	unsigned long long poly_hash_1(const string& s){
		unsigned long long m1 = 1000000007;
		unsigned long long x = 823;
		unsigned long long hash = 0;
		for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
			hash = (((hash * x + s[i] ) % m1 ) + m1) % m1;

		return hash;
	}
	unsigned long long poly_hash_2(const string& s){
		unsigned long long m2 = 1000000009;
		unsigned long long x = 823;
		unsigned long long hash = 0;
		for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
			hash = (((hash * x + s[i] ) % m2 ) + m2) % m2;

		return hash;
	}

public:	
	Solver(string s) : s(s) {	
		// initialization, precalculation
	}
	bool ask(int a, int b, int l) {
		if(poly_hash_1(s.substr(a, l)) != poly_hash_1(s.substr(b, l)))
			return false;
		if(poly_hash_2(s.substr(a, l)) != poly_hash_2(s.substr(b, l)))
			return false;

		return true;
	}
};

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	string s;
	int q;
	cin >> s >> q;
	Solver solver(s);
	for (int i = 0; i < q; i++) {
		int a, b, l;
		cin >> a >> b >> l;
		cout << (solver.ask(a, b, l) ? "Yes\n" : "No\n");
	}
}
