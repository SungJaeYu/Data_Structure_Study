#include <iostream>

using namespace std;

class Solver {
	string s;
	bool compare_hash(const string& a, const string& b){
		unsigned long long m1 = 1000000007;
		unsigned long long m2 = 1000000009;
		unsigned long long x = 263;
		unsigned long long hash1_a = 0;
		unsigned long long hash2_a = 0;
		unsigned long long hash1_b = 0;
		unsigned long long hash2_b = 0;
		for (int i = static_cast<int> (a.size()) - 1; i >= 0; --i){
			hash1_a = (hash1_a * x + a[i] ) % m1;
			hash2_a = (hash2_a * x + a[i] ) % m2;
		}
		for (int i = static_cast<int> (b.size()) - 1; i >= 0; --i){
			hash1_b = (hash1_b * x + b[i] ) % m1;
			hash2_b = (hash2_b * x + b[i] ) % m2;
		}

		if(hash1_a != hash1_b)
			return false;
		if(hash2_a != hash2_b)
			return false;
		return true;
	}

public:	
	Solver(string s) : s(s) {	
		// initialization, precalculation
	}
	bool ask(int a, int b, int l) {
		return compare_hash(s.substr(a, l), s.substr(b, l));
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
