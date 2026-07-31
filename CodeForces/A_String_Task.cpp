#include <bits/stdc++.h>
using namespace std;

bool isVowel(char c) {
    return c=='a' || c=='e' || c=='i' || c=='o' || c=='u' || c=='y';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    for (char c : s) {
        c = tolower(c);
        if (!isVowel(c))
            cout << "." << c;
    }

    cout << '\n';
}