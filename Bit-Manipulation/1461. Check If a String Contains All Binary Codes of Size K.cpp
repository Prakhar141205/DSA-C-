class Solution {
public:
    bool hasAllCodes(string s, int k) {
        unordered_set<string> st;

        int n = s.length();

        int codes = (1 << k) ;

        for(int i=0; i<=n - k; i++) {
            
            string temp = s.substr(i, k) ;

            if(st.find(temp) == st.end()) {
                st.insert(temp);
                codes--;
            }
            if(codes == 0) return true;
        }

        return false;
    }
};