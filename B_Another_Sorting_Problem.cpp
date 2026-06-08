#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    while(n--){
        int t;
        cin >> t;
        vector<int> v;
        v.reserve(t);
        unordered_set<int> st;
        int temp_t = t;
        while(t--){
            int x; 
            cin >> x;
            v.push_back(x);
        }

        for(int i=temp_t-1; i>0; i--){
            int x = v[i] - v[i-1];
            if(x < 0){
                st.insert(x);
            }
        }
        
        if(st.size() == 1 ) cout << "YES\n";
        else cout << "NO\n";

    }
    return 0;
}