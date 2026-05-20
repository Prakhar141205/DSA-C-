#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    unordered_set<int> s;
    int x = 2;
    while(x--){
        int p;
        cin >> p;
        for(int i=0; i<p; i++){
            int a;
            cin >> a;
            s.insert(a);
        }
        int q;
        cin >> q;
        for(int i=0; i<q; i++){
            int b;
            cin >> b;
            s.insert(b);
        }


    }

    if(s.size() == n) cout << "I become the guy.\n";
    else cout <<"Oh, my keyboard!\n";
    return 0;
}


// one more possible qpproach in o(n) is using bool vector