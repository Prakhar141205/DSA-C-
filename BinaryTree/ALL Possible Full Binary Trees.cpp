
class Solution {
public:
    typedef TreeNode* tt;
    vector<tt> solve(int n) {
        if(n%2 == 0) return {};

        if(n == 1) {
            tt root = new TreeNode(0);
            return {root};
        }
        vector<tt> ans;

        for(int i=1; i<n; i+=2) {
            vector<tt> L = solve(i);
            vector<tt> R = solve(n-i-1);

            for(tt node1 : L) {
                for(tt node2 : R) {
                    tt root = new TreeNode(0);
                    root->left = node1;
                    root->right = node2;
                    ans.push_back(root);
                }
            }
        }
        return ans;
    }
    vector<TreeNode*> allPossibleFBT(int n) {
        if(n % 2 == 0) return {};

        return solve(n);
    }
};

// Using Memoization

class Solution {
public:
    typedef TreeNode* tt;
    unordered_map<int, vector<tt>> mp;

    vector<tt> solve(int n) {
        if(n%2 == 0) return {};

        if(n == 1) {
            tt root = new TreeNode(0);
            return {root};
        }

        if(mp.find(n) != mp.end()) {
            return mp[n];
        }
        vector<tt> ans;

        for(int i=1; i<n; i+=2) {
            vector<tt> L = solve(i);
            vector<tt> R = solve(n-i-1);

            for(tt node1 : L) {
                for(tt node2 : R) {
                    tt root = new TreeNode(0);
                    root->left = node1;
                    root->right = node2;
                    ans.push_back(root);
                }
            }
        }
        return mp[n] = ans;
    }
    vector<TreeNode*> allPossibleFBT(int n) {
        if(n % 2 == 0) return {};
        mp.clear();
        return solve(n);
    }
};