#include <iostream>
#include <vector>
#include <string>
using namespace std;

void f(int n, int lPlace, string ans){

    if(n == 0) {
        cout << ans << "\n";
        return ;
    }
    if(lPlace  != 1){
        f(n-1, 0, ans + "0");
        f(n-1, 1, ans + "1");
    }else{
        f(n-1, 0, ans + "0");
    }
} 

int main(){
    int n = 3;
    string ans="";
    f(n, 0, ans);
    return 0;
}