class Solution {
public:
    string reverseWords(string s) {
        int n = s.length();
        stack<string> st;
        string ans = "";
        int i=0;
        while(i < n) {
            if(s[i] != ' ') break;
        }

        int j= n-1;
        while(j >= 0) {
            if(s[j] != ' ') break;
        }

        for(; i<=j; i++) {
            string temp = "";
            while(i <= j && s[i] != ' ') {
                temp += s[i];
                i++;
            }
            if(temp != "")
                st.push(temp);


        }

        while(st.size() > 1) {
            ans += st.top() + " ";
            st.pop();
        }

        ans += st.top();
        st.pop();

        return ans;
    }
};

class Solution {
public:
    // //  using cpp inbuilt tokenizer
    // string reverseWords(string s) {
    //     int n = s.length();
    //     stringstream ss(s);
    //     vector<string> words;
    //     string token;

    //     while(ss >> token){
    //         words.push_back(token);
    //     }

    //     reverse(words.begin(), words.end());
    //     string result;
    //     for(auto& w : words){
    //         result += w  + " ";
    //     }

    //     return result.substr(0, result.size()-1);
        
    // }

    string reverseWords(string s) {
        int n = s.length();
        reverse(s.begin(), s.begin() + n);
        int i=0;

        int l=0, r=0; // ye left or right pointers words kp reverse karenge

        while(i < n){

            while(i < n && s[i] != ' '){
                s[r++] = s[i++];
            }

            if(l < r){
                reverse(s.begin()+l, s.begin() + r );
                s[r] = ' ';
                r++;
                l = r;
            }

            i++;
        }
        s = s.substr(0, r-1);

        return s;
    }
};