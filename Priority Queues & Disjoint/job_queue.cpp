#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::priority_queue;

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
  struct FreeTime{
	  long long time;
	  int index;
	  FreeTime(long long t, int i):time(t), index(i){}
  };

  struct cmp{
	  bool operator()(FreeTime a, FreeTime b){
		  if(a.time == b.time)
			  return a.index > b.index;
		  return a.time > b.time;
	  }
  };

  void AssignJobs() {
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
	priority_queue<FreeTime, vector<FreeTime>, cmp > next_free_time;
	for ( int i = 0; i < num_workers_; ++i){
		next_free_time.push(FreeTime(0, i));
	}
    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
	  //Extract Min(Priority Queue)
	  start_times_[i] = next_free_time.top().time;
	  assigned_workers_[i] = next_free_time.top().index;
	  next_free_time.pop();
      
	  //Insert(next_free_time + duration)
	  next_free_time.push(FreeTime(start_times_[i] + duration, assigned_workers_[i]));
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
