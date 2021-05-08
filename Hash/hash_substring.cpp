#include <iostream>
#include <string>
#include <vector>

using std::string;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

long long poly_hash(const string& s){
	long long multiplier = 263;
	long long prime = 1000000007;
	long long hash = 0;
	for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
		hash = (((hash * multiplier + s[i] ) % prime)+ prime) % prime;
	return hash;
}

void pre_compute_hash(long long hash_arr[], const string& t, size_t pattern_size){
	long long x = 263;
	long long p = 1000000007;
	
	size_t len = t.size() - pattern_size + 1;
	string s = t.substr(len-1);
	hash_arr[len-1] = poly_hash(s);
	long long y = 1;
	for(int i = 0; i < pattern_size; ++i)
		y = ((y * x) % p + p) % p;
	for (int i = len - 2; i > -1; --i)
		hash_arr[i] = ((((x * hash_arr[i+1]) + t[i] - (y * t[i + pattern_size])) % p) + p ) % p;
}

std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
	std::vector<int> ans;
	long long hash_arr[t.size() - s.size() + 1];
	long long p_hash = poly_hash(s);
	pre_compute_hash(hash_arr, t, s.size());
    for (size_t i = 0; i + s.size() <= t.size(); ++i){
		if (p_hash != hash_arr[i])
			continue;
        if (t.substr(i, s.size()) == s)
            ans.push_back(i);
	}
    return ans;
}




int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
