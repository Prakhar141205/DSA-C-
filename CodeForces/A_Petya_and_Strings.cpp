#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s1, s2;

    cin >> s1 >> s2;

    int n1 = s1.size();
    int n2 = s2.size();


    // convert string one to lower character
    for(int i=0; i<n1; ++i){
        char x = s1[i];
        if(x >= 'A' && x <= 'Z'){
            s1[i] = x - 'A' + 'a';
        }
    }

    // convert string two to lower character
    for(int i=0; i<n2; ++i){
        char x = s2[i];
        if(x >= 'A' && x <= 'Z'){
            s2[i] = x - 'A' + 'a';
        }
    }
    
    if(!s1.compare(s2)){
        cout << 0 << "\n";
    }else{
         for(int i=0; i<n1; ++i){

            if(s1[i] > s2[i]) {
                cout << 1 <<"\n";
                break;
            }else if(s2[i] > s1[i]) {
                cout << -1 << "\n";
                 break;
            }
        }
   
    }

   
    
    
   
    return 0;
}