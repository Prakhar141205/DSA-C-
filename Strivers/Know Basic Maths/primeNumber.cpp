#include <iostream>
#include <vector>

using namespace std;

vector<int> findAllPrime(int n) {
    vector<bool> isPrime(n+1, true);
    isPrime[0] = false;
    isPrime[1] = false;
    
    for(int i=2; i*i <= n; i++) {

        for(int j=i*i; j<=n; j += i ) {

            if(isPrime[i]) {
                isPrime[i] = false;
            }
        }
    }
    return isPrime;
}


int  main() {
    for(int x : findAllPrime(5)) cout << x << " ";
    return 0;
}