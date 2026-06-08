#include <iostream>
#include <stack>
#include <vector>
#include <string>

using namespace std;

void helper(int i, int n, string ans, vector<string> &vec){
    if(i >= n){
        vec.push_back(ans);
        return;
    }

    helper(i+1, n, ans+'0', vec);

    if(ans.empty() || ans.back() != '1'){
        helper(i+1, n, ans+'1')
    }
}

void generateStrings(int n, vector<string>& vec){
    
    string ans = "";

    helper(0, n, ans, vec);
}
int main(){
    vector<string> vec;
    generateStrings(4, vec);
    
    for(string s : vec){
        cout << s << "\n";
    }
    return 0;
}