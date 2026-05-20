#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int year ;
    cin >> year;

    int ans = year;
    unordered_set<char> st;

    while(ans++ && ans <= 9000){
        string s = to_string(ans);

        for(char c : s){
            st.insert(c);
        }

        if(st.size() == 4){
            cout << ans << "\n";
            break;
        }else{
            st.clear();

        }
    }
    return 0;
}