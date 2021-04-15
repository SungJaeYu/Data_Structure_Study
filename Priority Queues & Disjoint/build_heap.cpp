#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void GenerateSwaps() {
    swaps_.clear();
	int size = data_.size();
	int parentsBound = size/2 - 1;
	for(int i = parentsBound; i >= 0; --i){
		SiftDown(i);
	}
  }

  void SiftDown(int i) {
		int size = data_.size();
	    int maxIndex = i;
		int left = 2 * i + 1;
		if( left < size && data_[left] < data_[maxIndex] )
			maxIndex = left;
		int right = 2 * i + 2;
		if( right < size && data_[right] < data_[maxIndex] )
			maxIndex = right;
		if( i != maxIndex ){
			swap(data_[i], data_[maxIndex]);
			swaps_.push_back(make_pair(i, maxIndex));
			SiftDown(maxIndex);
		}
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
