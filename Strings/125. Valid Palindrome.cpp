class Solution {
public:
    bool isPalindrome(string s) {
        int st = 0;
        int end = s.length()-1;

        while(st < end){

            while(st < end && !isalnum(s[st])) st++;
            while(st < end && !isalnum(s[end])) end--;

            if(tolower(s[st]) != tolower(s[end])) return false;
            
            

            st++;end--;
        }
        return true;
    }
};

class Solution {
private:
    bool isValid(char ch) {
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ||
            (ch >= '0' && ch <= '9')) {
            return 1;
        } else {
            return 0;
        }
    }

    char toLowerCase(char ch) {
        if ((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9')) {
            return ch;
        } else {
            char temp = ch - 'A' + 'a';
            return temp;
        }
    }

public:
    bool isPalindrome(string s) {
        string temp = "";
        for (int j = 0; j < s.length(); j++) {
            if (isValid(s[j])) {
                temp.push_back(s[j]);
            }
        }

        for (int j = 0; j < temp.length(); j++) {
            temp[j] = toLowerCase(temp[j]);
        }
        int n = temp.length();
        for (int i = 0; i < temp.length(); i++) {
            if (temp[i] != temp[n - i - 1]) {
                return false;
            }
        }
        return true;
    }
};