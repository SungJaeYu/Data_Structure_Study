#include <iostream>
#include <vector>
#include <deque>

using std::cin;
using std::cout;
using std::vector;
using std::max;

void max_sliding_window_naive(vector<int> const & A, int w) {
    for (size_t i = 0; i < A.size() - w + 1; ++i) {
        int window_max = A.at(i);
        for (size_t j = i + 1; j < i + w; ++j)
            window_max = max(window_max, A.at(j));

        cout << window_max << " ";
    }

    return;
}

void max_sliding_window(vector<int> const & A, int w) {
	std::deque<int> Qi(w);
	
	int i;
	for(i = 0; i < w; ++i){
		while((!Qi.empty()) && A[i] >= A[Qi.back()])
			Qi.pop_back();
		Qi.push_back(i);
	}

	for(; i< A.size(); ++i){
		cout << A[Qi.front()] << " ";
		while((!Qi.empty()) && Qi.front() <= i - w)
			Qi.pop_front();
		while((!Qi.empty()) && A[i] >= A[Qi.back()])
			Qi.pop_back();
		Qi.push_back(i);
	}
	cout << A[Qi.front()];
}


int main() {
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;

    max_sliding_window(A, w);

    return 0;
}
