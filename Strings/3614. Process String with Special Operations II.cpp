class Solution {
public:
    char processStr(string s, long long k) {
        int n = s.length();
        long long int L=0;
        for(char& c: s){
            if(c >= 'a' && c <= 'z'){
                L++;
                

            }else if(c == '*'){
                if(L > 0) L--;
            }else if(c == '#'){
                L *= 2;
                
            }else if(c == '%'){
                // reverse(res.begin(), res.end());
                continue;
                // no change in L
            }
        }

        if(k >= L) return '.';

        for(int i=n-1; i>=0; i--){
            char c = s[i];
            if(c >= 'a' && c <= 'z'){
                L--;
                

            }else if(c == '*'){
                L++;

            }else if(c == '#'){
                L = L/2;
                if(k >= L){
                    k = k-L;
                }
                
            }else if(c == '%'){
                k = L-k-1;
            }

        if(k == L) return s[i];

        }
        return '.';
    }
};