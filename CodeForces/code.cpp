#include <bits/stdc++.h>
using namespace std;

int closestNumber(int n, int m){ // O(N)
    int closest = 0;
    int minDiff = INT_MAX;
    for(int i= n- abs(m); i <= n + abs(m); ++i){
        int diff = n - i ;
        if(diff < minDiff || (diff == minDiff && abs(i) > abs(closest)) ){
            closest = i;
            minDiff = diff;
        }
    }
    return closest;

}

int closestNumberOptim(int n, int m){
    // find quotient of n / m

    int q = n/m;
   
    // 1st possible closest number
    int n1 = m * q;
    
    // 2nd possible closest number
    int n2 = (n * m) > 0 ? (m * (q + 1)) : (m * (q - 1));
    
    // if true, then n1 is the required closest number

    return (abs(n-n2)> abs(n-n1)) ? n1 : n2 ;
}

int printSum(int n){
    if(n == 0) return 0;
    return ((n%10)+printSum(n/10));
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    
    cout << closestNumberOptim(15, 4);
    cout << printSum(1234);
    
    return 0;
}