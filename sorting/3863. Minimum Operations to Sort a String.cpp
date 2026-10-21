class Solution {
public:
    int minOperations(string s) {
        string target = s;
        sort(target.begin(), target.end());

        if (s == target) return 0;

        queue<string> q;
        unordered_set<string> visited;

        q.push(s);
        visited.insert(s);

        int steps = 0;

        while (!q.empty()) {
            int size = q.size();

            while (size--) {
                string curr = q.front();
                q.pop();

                if (curr == target) {
                    return steps;
                }

                int n = curr.size();

                for (int i = 0; i < n; i++) {
                    for (int j = i + 1; j < n; j++) {
                        string next = curr;

                        swap(next[i], next[j]);

                        if (visited.find(next) == visited.end()) {
                            visited.insert(next);
                            q.push(next);
                        }
                    }
                }
            }

            steps++;
        }

        return -1;
    }
};

// Using Optimal Approach
class Solution {
public:
    int minOperations(string s) {
       int n = s.length();
        if(is_sorted(begin(s), end(s))) return 0;
       if(n == 2) return -1;

       char min_char = *min_element(begin(s), end(s));
       char max_char = *max_element(begin(s), end(s));

       if(s[0] == min_char or s[n-1] == max_char) return 1;

       char max_mid = *max_element(begin(s) + 1, end(s) - 1);
       char min_mid = *min_element(begin(s)  + 1, end(s) - 1);

       if(s[0] > max_char and s[n-1] < min_mid) return 3;

       return 2;
    }
};