#include <iostream>
#include <vector>

int reverseNumber(int n){
    int revN = 0;

    while(n){
        int d = n % 10
        revN = revN * 10 + d ; 
        n /= 10;
    }
    return revN;
}
int main(){
    int N = 1123242;

    cout << "Reversed number: " << reverseNumber(int n) << "\n";
    return 0;
}