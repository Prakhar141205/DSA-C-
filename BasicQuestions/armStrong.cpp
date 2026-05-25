#include <bits/stdc++.h>
using namespace std;

// Class to check Armstrong number
class ArmstrongChecker {
public:
    // Static method to check if a number is an Armstrong number
    static bool isArmstrong(int num) {
        int k = to_string(num).length(); // Get number of digits
        int sum = 0;
        int n = num;

        while (n > 0) {
            int ld = n % 10;            // Get last digit
            sum += pow(ld, k);          // Add ld^k to sum
            n /= 10;                    // Remove last digit
        }

        return sum == num; // Return true if sum equals original number
    }
};

int main() {
    int number = 153;

    // Use class method to check
    if (ArmstrongChecker::isArmstrong(number)) {
        cout << number << " is an Armstrong number." << endl;
    } else {
        cout << number << " is not an Armstrong number." << endl;
    }

    return 0;
}
