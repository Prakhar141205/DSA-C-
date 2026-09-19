#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

class Solution {
public:
    void findSecondLargest(vector<int>& arr) {
        int secondLargest = INT_MIN;
        int largest = INT_MIN;

        for(int& x : arr ) {

            if(x > largest) {
                secondLargest = largest;
                largest = x ;
            }else if(x > secondLargest && x != largest) {
                secondLargest = x ;
            }
        }

        cout << "Largest: " << largest << "\n";
        cout << "Second Largest: " << secondLargest << "\n";
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> arr = {-1, -2, -3, -4, -5, -6, -2, -6, -8};

    Solution sol1 ;
    sol1.findSecondLargest(arr) ;

    return 0;
}


if (s[i] != t[j]) {
    int del_i = s[i] + solve(i-1, j);
    int del_j = s[j] + solve(i, j-1);
    return min(del_i, del_j);
}else {
    return solve(i-1, j-1) ;
}