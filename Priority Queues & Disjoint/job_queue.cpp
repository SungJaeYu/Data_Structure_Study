#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector< pair <int, long long> > next_free_time(num_workers_);
	for (int i = 0; i < num_workers_; ++i) {
		next_free_time[i] = make_pair(i, 0);
	}
    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
	  //Extract Min(Priority Queue)
	  start_times_[i] = next_free_time[0].second;
	  assigned_workers_[i] = next_free_time[0].first;
	  swap(next_free_time[0], next_free_time[num_workers_ - 1]);
	  next_free_time.pop_back();
	  SiftDown(next_free_time, 0);
      
	  //Insert(next_free_time + duration
      next_free_time.push_back(make_pair(assigned_workers_[i], start_times_[i] + duration));
	  SiftUp(next_free_time, num_workers_ - 1);
    }
  }

  void SiftDown(vector < pair <int, long long> > &nft, int i){
	  int maxIndex = i;
	  int left = 2 * i + 1;
	  int right = 2 * i + 2;
	  if ( left < num_workers_ && nft[left].second < nft[maxIndex].second )
		  maxIndex = left;
	  if ( right < num_workers_ && nft[right].second < nft[maxIndex].second )
		  maxIndex = right;
	  if ( i != maxIndex ){
		  swap(nft[i], nft[maxIndex]);
		  SiftDown(nft, maxIndex);
	  }
  }

  void SiftUp(vector < pair <int, long long> > &nft, int i){
	  int parent = (i + 1)/2 - 1;
	  while( i > 0 && nft[parent].second > nft[i].second){
	       swap(nft[parent], nft[i]);
		   i = parent;
		   parent = (i + 1)/2 - 1;
	  }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
