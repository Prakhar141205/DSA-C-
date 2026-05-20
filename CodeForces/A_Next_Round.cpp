#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

   int n, k;
   cin >>n >> k;
    int count=0;
    int kthScore;
    vector<int> score(n);
   for(int i=0; i<n; ++i){
        int x;
        cin >> x;
        if(i == k-1)  kthScore=x;
        score.push_back(x);
   }

   for(int i=0; i< score.size(); ++i){
    if(score[i] > 0 && score[i] >= kthScore) count++;
   }

   cout << count << "\n";
    return 0;
}