#include <iostream>
#include <string>
#include <vector>

int main() {
    int num = 12345;
    std::string s = std::to_string(num);
    
    // Extract and print all prefixes
    for (size_t i = 1; i <= s.length(); ++i) {
        std::cout << s.substr(0, i) << std::endl;
    }
    
    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int num = 12345;
    std::vector<int> prefixes;
list<int>
    // Remove one digit at a time to get prefixes
    while (num > 0) {
        prefixes.push_back(num);
        num /= 10;
    }

    // Reverse to show from shortest to longest
    std::reverse(prefixes.begin(), prefixes.end());

    for (int p : prefixes) {
        std::cout << p << std::endl;
    }

    return 0;
}
