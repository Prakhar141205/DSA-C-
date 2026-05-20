#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 5;
    int input, answer;
    int R1, C1;

    while(n--){
        vector<int> row(5);
        for(int i=0; i<=4; i++){
            cin >> input ;
            if(input == 1){
                R1 = 5-n;
                C1 = i+1;
            }
            row[i] = input;
        }
    }

    

    
    cout <<  abs(3-R1) + abs(3-C1)<<"\n";
    
    return 0;
}