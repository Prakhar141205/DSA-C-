/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    void dfs(TreeNode* root, string& s) {
        if(!root) {
            s += "*,";
            return;
        }

        s += (to_string(root->val) + ",");
        dfs(root->left, s);
        dfs(root->right, s);
    }
    string serialize(TreeNode* root) {
        string s;
        dfs(root, s);
        return s;
    }

    // Decodes your encoded data to tree.
    TreeNode* build(vector<string>& nodes, int& idx) {
        if(nodes[idx] == "*") {
            idx++;
            return nullptr;
        }

        TreeNode* root = new TreeNode(stoi(nodes[idx]));
        idx++;

        root->left = build(nodes, idx);
        root->right = build(nodes, idx);

        return root;
    }
    TreeNode* deserialize(string data) {
        vector<string> ans;
        string token;
        stringstream ss(data);
         
        while(getline(ss, token, ',')) {
            if(!token.empty()){
                ans.push_back(token);
            }
        }

        int idx = 0;
        return build(ans, idx);
        
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));