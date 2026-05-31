class Solution {
public:
    int numberOfSpecialChars(string s) {
        int arra[26] = {0};
        int arrA[26] = {0};
        int n = s.size();

        for(int i=0; i<n; i++){
            char x = s[i];
            if(x >= 'a' && x <= 'z') arra[x-'a']++;
            else arrA[x - 'A']++;
        }
        int cnt=0;
        for(int i=0; i<26; i++){
            if(arra[i] > 0 && arrA[i] > 0 ) cnt++;
        }
        return cnt;
    }
};


class Solution {
public:
    int numberOfSpecialChars(string word) {
        int or_lower = 0, or_upper = 0;
        for(char ch : word){
            if(islower(ch)){
                or_lower |= (1<< (ch-'a'));
            }else{
                or_upper |= (1<< (ch-'A'));
            }
        }
        
        int ans=0;
        for(int i=0;i<26;i++){
            if(or_lower & (1<<i) && or_upper & (1<<i)) ans++;
        }
        
        return ans;
    }
};

class Solution {
public:
    int numberOfSpecialChars(string word) {
        unordered_set<char> s(word.begin(), word.end());
        int ans = 0;
        for (char c = 'a'; c <= 'z'; c++) {
            if (s.count(c) && s.count(c - 'a' + 'A')) {
                ans++;
            }
        }
        return ans;
    }
};