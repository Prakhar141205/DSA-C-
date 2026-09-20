/*
# Function to check if a given number is prime
def checkPrime(n):
    cnt = 0  # Initialize a counter variable to count the number of factors

    # Loop through numbers from 1 to the square root of n
    for i in range(1, int(n ** 0.5) + 1):
        if n % i == 0:
            cnt += 1  # If n is divisible by i, increment the counter

            # If n is not a perfect square, count its reciprocal factor
            if n // i != i:
                cnt += 1

    # If the number of factors is exactly 2 (1 and the number itself), it's prime
    return cnt == 2

# Driver code
n = 1483  # Example number
isPrime = checkPrime(n)  # Function call to check if the number is prime

if isPrime:
    print(f"{n} is a prime number.")
else:
    print(f"{n} is not a prime number.")

# Optimal Sieve of Erathothenis

def sieve(n):
    is_prime = [True] * (n + 1)

    is_prime[0] = is_prime[1] = False

    for i in range(2, int(n ** 0.5) + 1):
        if is_prime[i]:
            for j in range(i * i, n + 1, i):
                is_prime[j] = False

    return is_prime


n = 20
is_prime = sieve(n)

for i in range(2, n + 1):
    if is_prime[i]:
        print(i, end=" ")

        */
        
#include <iostream>
#include <vector>
using namespace std;

vector<int> findAllDivisor(int n) {
    vector<int> ans;
    for(int i=0; i*i <= n; i++) {

        if(n%i == 0) ans.push_back(i);

        if(i != n/i ) ans.push_back(n/i);
    }

    return ans;

}

int main() {
    int n = 8;

    for(int x : findAllDivisor(n)) cout << x << " ";
    return 0;
}