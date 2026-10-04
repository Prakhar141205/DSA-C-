class Solution {
public:
    bool isIsomorphic(string s, string t) {
        unordered_map<char, char> mp1; // s ==> t
        unordered_map<char, char> mp2; //  t ==> s
        
        for(int i=0; i<s.length(); i++) {
            char c1 = s[i];
            char c2 = t[i];

            if((mp1.find(c1) != mp1.end() && mp1[c1] != c2) || (mp2.find(c2) != mp2.end() && mp2[c2] != c1)) return false;

            mp1[c1] = c2;
            mp2[c2] = c1;
        }

        return true;
    }
};