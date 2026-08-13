// brute force 

class Solution {
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        int n = s.length();
        // unordered_map<int, char> mp;
        int k = queryCharacters.length();

        vector<int> res;
        for(int i=0; i<k; i++) {
            s[queryIndices[i]] = queryCharacters[i] ;

            cout << s << "\n";
            int ans = 0 ;
            int cnt = 1;
            for(int i=1; i<n; i++) {
                if(s[i] == s[i-1]) {
                    cnt++;
                }else {
                    ans = max(cnt, ans) ;
                    cnt = 1 ;
                }
            }

            ans = max(ans, cnt) ;
            res.push_back(ans) ;
            ans = 0;
        }



        
        return res ;
    }
};

// using multiset
class Solution {
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        int n = s.length();
        int k = queryCharacters.size();

        vector<int> ans;

        set<pair<int, int>> runs;
        multiset<int> lengths;

        int start = 0;

        for(int i = 1; i <= n; i++) {
            if(i == n || s[i] != s[start]) {
                runs.insert({start, i - 1});

                int len = i - start;
                lengths.insert(len);

                start = i;
            }
        }

        for(int i = 0; i < k; i++) {
            int pos = queryIndices[i];
            char ch = queryCharacters[i];

            if(ch == s[pos]) {
                ans.push_back(*lengths.rbegin());
                continue;
            }

            auto it = runs.upper_bound({pos, n});
            --it;

            int l = it->first;
            int r = it->second;

            int oldLen = r - l + 1;

            lengths.erase(lengths.find(oldLen));
            runs.erase(it);

            if(l < pos) {
                runs.insert({l, pos - 1});
                lengths.insert(pos - l);
            }

            if(pos < r) {
                runs.insert({pos + 1, r});
                lengths.insert(r - pos);
            }

            s[pos] = ch;

            int newL = pos;
            int newR = pos;

            if(pos > 0 && s[pos - 1] == s[pos]) {
                auto left = runs.upper_bound({pos - 1, n});
                --left;

                int ll = left->first;
                int lr = left->second;

                lengths.erase(lengths.find(lr - ll + 1));
                runs.erase(left);

                newL = ll;
            }

            if(pos + 1 < n && s[pos + 1] == s[pos]) {
                auto right = runs.upper_bound({pos, n});

                int rl = right->first;
                int rr = right->second;

                lengths.erase(lengths.find(rr - rl + 1));
                runs.erase(right);

                newR = rr;
            }

            runs.insert({newL, newR});
            lengths.insert(newR - newL + 1);

            ans.push_back(*lengths.rbegin());
        }

        return ans;
    }
};