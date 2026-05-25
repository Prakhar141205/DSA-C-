#include <iostream>
#include <vector>
using namespace std;

vector<int> sieve(int n) {
    
    // creation of boolean array
    vector<bool> prime(n + 1, true);
    for (int p = 2; p * p <= n; p++) {
        if (prime[p] == true) {
            
            // marking as false
            for (int i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }
    
    vector<int> res;
    for (int p = 2; p <= n; p++){
        if (prime[p]){ 
            res.push_back(p);
        }
    }
    return res;
}

int main(){
    int n = 35;
    vector<int> res = sieve(n);
    for(auto ele : res){
        cout << ele << ' ';
    }
    return 0;
}



// def sieve_of_eratosthenes(n):
//     # Create a boolean array "prime[0..n]" and initialize
//     # all entries it as true. A value in prime[i] will
//     # finally be false if i is Not a prime, else true.
//     prime = [True for _ in range(n + 1)]
//     p = 2
//     while (p * p <= n):
//         # If prime[p] is not changed, then it is a prime
//         if (prime[p] == True):
//             # Update all multiples of p
//             for i in range(p * p, n + 1, p):
//                 prime[i] = False
//         p += 1
    
//     # Return a list of all primes
//     return [p for p in range(2, n + 1) if prime[p]]

// # Example usage:
// print(sieve_of_eratosthenes(30))
// # Output: [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]
