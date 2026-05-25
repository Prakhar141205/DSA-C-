#include <iostream>
#include <vector>
bool sieve(int n){
    bool arr[n+1];

    std::fill(arr, arr+n+1, true);

    for(int p=2; p*p <= n; p++){
        if(arr[p]){
            for(int i=p*p; i<=n; i+=p){
                arr[i]=false;
            }
        }
    }
    return arr[n];
}
int main(){
    int n = 15;
    std::cout << sieve(n);
    return 0;
}