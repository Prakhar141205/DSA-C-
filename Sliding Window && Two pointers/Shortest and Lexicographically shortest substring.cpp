class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {

        int n = s.length();
        string res = "";
        for(int len=k; len <= n; len++) {
            string res = "";

            for(int st=0; st <= n - len; st++) {
                string temp = s.substr(st, len);

                auto cnt = count(temp.begin(), temp.end(), '1');

                if(cnt == k) {
                    if(res.empty() || temp < res) {
                        res = temp;
                    }
                }
                
            }
            if(!res.empty()) {
                    return res;
                }
        }

        return "";
        
    }
};

// Sliding Window : Second type implementation

class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        if (ranges::count(s, '1') < k) {
            return "";
        }
        string ans = s;
        int cnt = 0;
        for (int left = 0, right = 0; right < s.length(); right++) {
            cnt += s[right] - '0';
            while (cnt > k || s[left] == '0') {
                cnt -= s[left] - '0';
                left++;
            }
            if (cnt == k) {
                string t = s.substr(left, right - left + 1);
                if (t.length() < ans.length() ||
                    t.length() == ans.length() && t < ans) {
                    ans = move(t);
                }
            }
        }
        return ans;
    }
};