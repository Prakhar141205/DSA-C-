
class Solution {
public:
    
        
    string DFS(TreeNode* root, unordered_map<string, int>& mp, vector<TreeNode*>& res){
        if(root == NULL) 
            return "NULL";
        
        string s = to_string(root->val) + "," + DFS(root->left, mp, res) + "," + DFS(root->right, mp, res);
        
        if(mp[s] == 1)
            res.push_back(root);
        
        mp[s]++;
        
        return s;
    }
    
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        unordered_map<string, int> mp;
        
        vector<TreeNode*>res;
        
        DFS(root, mp, res);
        
        return res;
    }

};


class Solution {
public:

    bool isSame(TreeNode* a, TreeNode* b) {

        if (!a && !b) return true;

        if (!a || !b) return false;

        if (a->val != b->val) return false;

        return isSame(a->left, b->left) &&
               isSame(a->right, b->right);
    }

    void storeNodes(TreeNode* root, vector<TreeNode*>& nodes) {

        if (!root) return;

        nodes.push_back(root);

        storeNodes(root->left, nodes);
        storeNodes(root->right, nodes);
    }

    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {

        vector<TreeNode*> nodes;
        storeNodes(root, nodes);

        int n = nodes.size();

        vector<TreeNode*> ans;

        unordered_set<TreeNode*> added;

        for (int i = 0; i < n; i++) {

            for (int j = i + 1; j < n; j++) {

                if (isSame(nodes[i], nodes[j])) {

                    if (added.find(nodes[i]) == added.end()) {
                        ans.push_back(nodes[i]);
                        added.insert(nodes[i]);
                    }

                    break;
                }
            }
        }

        return ans;
    }
};
