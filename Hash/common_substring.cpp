#include <iostream>

using namespace std;

struct Answer {
	size_t i, j, len;
};

unsigned long long poly_hash1(const string& s){
	static const size_t x = 31;
	static const size_t p = 1000000007;
	unsigned long long hash = 0;
	for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
		hash = (hash * x + s[i] ) % p;
	return hash;
}

unsigned long long poly_hash2(const string& s){
	static const size_t x = 31;
	static const size_t p = 1000000009;
	unsigned long long hash = 0;
	for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
		hash = (hash * x + s[i] ) % p;
	return hash;
}

void precompute_1(unsigned long long hash_arr[], const string& t, size_t len){
	static const size_t x = 31;
	static const size_t p1 = 1000000007;
	
	size_t hash_len = t.size() - len + 1;
	string s = t.substr(hash_len - 1);
	hash_arr[hash_len - 1] = poly_hash1(s);
	unsigned y = 1;
	for (int i = 0; i < len; ++i)
		y = (y * x) % p1;
	for (int i = hash_len - 2; i > -1; --i)
		hash_arr[i] = ((x * hash_arr[i+1]) + t[i] - (y * t[i + len])) % p1;
}

void precompute_2(unsigned long long hash_arr[], const string& t, size_t len){
	static const size_t x = 31;
	static const size_t p2 = 1000000009;
	
	size_t hash_len = t.size() - len + 1;
	string s = t.substr(hash_len - 1);
	hash_arr[hash_len - 1] = poly_hash2(s);
	unsigned y = 1;
	for (int i = 0; i < len; ++i)
		y = (y * x) % p2;
	for (int i = hash_len - 2; i > -1; --i)
		hash_arr[i] = ((x * hash_arr[i+1]) + t[i] - (y * t[i + len])) % p2;
}



Answer solve(const string &s, const string &t) {
	Answer ans = {0, 0, 0};
	size_t max_sub_len = (s.size() > t.size())? t.size() : s.size();
	unsigned long long hash_s_1[s.size()];
	unsigned long long hash_t_1[t.size()];
	
	unsigned long long hash_s_2[s.size()];
	unsigned long long hash_t_2[t.size()];

	for (size_t i = 1; i <= max_sub_len; i++){
		std::cout << "sub size : " << i << std::endl;
		precompute_1(hash_s_1, s, i);
		precompute_1(hash_t_1, t, i);

		precompute_2(hash_s_2, s, i);
		precompute_2(hash_t_2, t, i);

		size_t hash_size_s = s.size() - i + 1;
		size_t hash_size_t = t.size() - i + 1;
		for (size_t is = 0; is < hash_size_s; ++is){
			for (size_t it = 0; it < hash_size_t; ++it){
				if(hash_s_1[is] != hash_t_1[it])
					continue;
				if(hash_s_2[is] != hash_t_2[it])
					continue;
				ans = {is, it, i};
			}
		}
	}
	return ans;

}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	string s, t;
	while (cin >> s >> t) {
		auto ans = solve(s, t);
		cout << ans.i << " " << ans.j << " " << ans.len << "\n";
	}
}
