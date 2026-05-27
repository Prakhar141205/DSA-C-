#include <iostream>
#include <string>
#include <vector>

void reverseArray(int* arr, int n, int i){
    if( i >= n) return ;

    std::swap(arr[n], arr[i]);
    reverseArray(arr, n-1, i+1);
}

void printFib(int n){
    
    std:: cout << 0 << " " << 1 << " ";
    int p=0;
    int pp=1;

    for(int i=2; i<=n; i++){
        int curr = p + pp;
        std::cout << curr << " ";
        p = pp;
        pp = curr;
    }
}
int main(){
    int n  = 5;
    printFib(n);
    return 0;
}