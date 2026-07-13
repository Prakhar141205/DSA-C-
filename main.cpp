#include <iostream>
#include <string>

using namespace std;


int main() {
    string s = "123";

    for(int i=0; i<3; i++) {
        s[i] = s[i] + '1';
    }
    return 0;
}