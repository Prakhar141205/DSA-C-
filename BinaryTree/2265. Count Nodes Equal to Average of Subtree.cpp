
class Solution {
public:
    typedef TreeNode* tt;

    pair<int, int> getSumNodes(tt root) {
        if(!root) return {0, 0};

        pair<int, int> l = getSumNodes(root->left);
        pair<int, int> r = getSumNodes(root->right);

        return {l.first + r.first + root->val, l.second + r.second + 1};
    }
    int cnt = 0;
    void solve(tt root) {
        if(!root) return ;

        auto p = getSumNodes(root);
        int s = p.first;
        int ns = p.second;
        int avg = s/ns;

        if(avg == root->val) {
            cnt++;
        }
        solve(root->left);
        solve(root->right);
        
    }
    int averageOfSubtree(TreeNode* root) {
        if(!root) return 0;

        solve(root);
        return cnt;
    }
};

