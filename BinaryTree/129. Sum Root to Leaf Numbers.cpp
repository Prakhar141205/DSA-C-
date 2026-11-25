
/***************************************************** C++ *************************************/
//Recursion-1
//T.C : O(n)
//S.C : O(1)
class Solution {
public:
    
    int find(TreeNode* root, int curr) {
        
        if(!root)
            return 0;
        
        curr = curr*10 + root->val;
        
        if(root->left == NULL && root->right == NULL) {
            return curr;
        }
        
        int left_num  = find(root->left, curr);
        int right_num = find(root->right, curr);
        
        return left_num + right_num;
    }
    
    int sumNumbers(TreeNode* root) {
        return find(root, 0);
    }


};


class Solution {
public:
    int sum = 0;

    void dfs(TreeNode* root, int currNum) {

        if (!root) return;

        currNum = currNum * 10 + root->val;

        if (!root->left && !root->right) {
            sum += currNum;
            return;
        }

        dfs(root->left, currNum);
        dfs(root->right, currNum);
    }

    int sumNumbers(TreeNode* root) {

        sum = 0;
        dfs(root, 0);

        return sum;
    }
};


class Solution {
public:
    typedef long long ll;
    ll sum = 0;

    void allPaths(TreeNode* root, string& temp) {

        if (!root) return;

        int oldSize = temp.size();

        // Append current node's value
        temp += to_string(root->val);

        // Check if leaf node
        if (!root->left && !root->right) {
            sum += stoll(temp);
        }

        allPaths(root->left, temp);
        allPaths(root->right, temp);

        // Backtrack
        temp.resize(oldSize);
    }

    int sumNumbers(TreeNode* root) {

        sum = 0;

        if (!root) return 0;

        string temp = "";

        allPaths(root, temp);

        return sum;
    }
};


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public: 
    typedef long long ll;
    ll sum = 0;

    void allPaths(TreeNode* root, string& temp) {
        if(!root) return;
        temp.push_back(root->val + '0');
        if(!root->left and !root->right) {
            if (temp != "")
                sum += std::stoll(temp);
            temp.pop_back();
            return;
        }

        allPaths(root->left, temp);
        allPaths(root->right, temp);

        temp.pop_back();
    }
    int sumNumbers(TreeNode* root) {
        if(!root) return 0;
        string temp = "";
        allPaths(root, temp);


        return sum ;
    }
};


