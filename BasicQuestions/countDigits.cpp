#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// TC O(logN) base 10
int countDigits(int N){

    int cnt=0;

    while(N){
        cnt++;
        N/=10;
    }
    return cnt;
}

// constant TC O(1)
int countDigits(int n){
    return (int)(log10(n) + 1);
}

int main(){
    int N = 1324743284;

    cout << "The number of digit in N: " << countDigits(N) << "\n";; 

    return 0;
}


// python language

// import math

// # Calculate the count of digits in 'n'
// # using logarithmic operation log10(n) + 1.
// def countDigits(n):
//     # Initialize a variable 'cnt' to
//     # store the count of digits.
//     cnt = int(math.log10(n) + 1)

//     # The expression int(math.log10(n) + 1)
//     # calculates the number of digits in 'n'
//     # and casts it to an integer.
    
//     # Adding 1 to the result accounts
//     # for the case when 'n' is a power of 10,
//     # ensuring that the count is correct.
   
//     # Finally, the result is cast
//     # to an integer to ensure it is rounded
//     # down to the nearest whole number.
    
//     # Return the count of digits in 'n'.
//     return cnt

// # Main function
// if __name__ == "__main__":
//     N = 329823
//     print("N:", N)
//     digits = countDigits(N)
//     print("Number of Digits in N:", digits)
