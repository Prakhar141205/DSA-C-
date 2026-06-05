#include <iostream>
#include <vector>

using namespace std;

class Job {
    int deadLine;
    int profit;
    int idx;

    Job(int d, int p, int i){
        deadLine = d;
        profit = p;
        idx = i;
    }
    
};

int maxProfit(vector<pair<int, int>> jobs){
    int ans = 0, n = jobs.size();

    sort(jobs.begin(), jobs.end())
}
int main() {
    vector<pair<int, int >> jobs(4, {0, 0});

    jobs.push_back({1, 40});
    jobs.push_back({1, 30});
    jobs.push_back({4, 20});
    jobs.push_back({1, 10});
    return 0;
}