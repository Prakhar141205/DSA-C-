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
    string tree2str(TreeNode* root) {
        if(!root) return "";

        string result = to_string(root->val);

        string LEFT = tree2str(root->left);
        string RIGHT = tree2str(root->right);

        if(!root->left and !root->right) return result;
        if(root->left == NULL) {
            return result + "()" +  "(" + RIGHT + ")" ;
        }

        if(root->right == NULL) {
            return result + "(" + LEFT + ")";
        }

        return result + "(" + LEFT + ")" + "(" + RIGHT + ")";
    }
};


/*
LeetCode 606: Construct String from Binary Tree
Approaches from straightforward recursion to iterative traversal.

LeetCode provides TreeNode. Copy ONE Solution class and rename it to Solution.

Rule:
- Print node value in preorder.
- If left OR right child exists, print '(' + left representation + ')'.
- If right child exists, print '(' + right representation + ')'.
- If left is missing but right exists, the empty left representation produces ().
*/
#include <bits/stdc++.h>
using namespace std;

/*
APPROACH 1: Recursive — return a string for each subtree
Time: O(n) typical, but repeated temporary-string copying can be O(n^2)
in the worst case. Auxiliary space: O(h) recursion stack plus temporaries.
*/
class Solution1 {
private:
    string build(TreeNode* node) {
        if (node == nullptr) return "";

        string result = to_string(node->val);

        if (node->left != nullptr || node->right != nullptr) {
            result += "(";
            result += build(node->left);
            result += ")";
        }

        if (node->right != nullptr) {
            result += "(";
            result += build(node->right);
            result += ")";
        }

        return result;
    }

public:
    string tree2str(TreeNode* root) {
        return build(root);
    }
};

/*
APPROACH 2: Recursive — append to one shared output string (RECOMMENDED)
Time: O(n) amortized. Auxiliary space: O(h) recursion stack, excluding output.
*/
class Solution2 {
private:
    void build(TreeNode* node, string& result) {
        if (node == nullptr) return;

        result += to_string(node->val);

        if (node->left != nullptr || node->right != nullptr) {
            result += '(';
            build(node->left, result);
            result += ')';
        }

        if (node->right != nullptr) {
            result += '(';
            build(node->right, result);
            result += ')';
        }
    }

public:
    string tree2str(TreeNode* root) {
        string result;
        build(root, result);
        return result;
    }
};

/*
APPROACH 3: Iterative preorder using an explicit stack of traversal frames
Time: O(n) amortized. Auxiliary space: O(h), worst-case O(n).
This avoids recursive function calls.
*/
class Solution3 {
    struct Frame {
        TreeNode* node;
        int state; // 0 = print value/open left, 1 = close left/open right, 2 = close right/pop
    };

public:
    string tree2str(TreeNode* root) {
        if (root == nullptr) return "";

        string result;
        vector<Frame> st;
        st.push_back({root, 0});

        while (!st.empty()) {
            Frame& f = st.back();
            TreeNode* node = f.node;

            if (f.state == 0) {
                result += to_string(node->val);
                f.state = 1;

                if (node->left != nullptr || node->right != nullptr) {
                    result += '(';
                    if (node->left != nullptr) {
                        st.push_back({node->left, 0});
                    } else {
                        // Right child exists but left does not: required "()".
                        result += ')';
                    }
                }
            } else if (f.state == 1) {
                f.state = 2;

                if (node->left != nullptr || node->right != nullptr) {
                    // Close the left-child parentheses (or the empty left pair).
                    // If left was absent, its ')' was already emitted above.
                    if (node->left != nullptr) result += ')';
                }

                if (node->right != nullptr) {
                    result += '(';
                    st.push_back({node->right, 0});
                }
            } else {
                if (node->right != nullptr) result += ')';
                st.pop_back();
            }
        }

        return result;
    }
};

/*
APPROACH 4: Recursive variant — direct recurrence
This is the same core idea as Approach 1, expressed as:
node value + optional (left) + optional (right).
It is useful for understanding the formatting rule but has the same potential
temporary-string-copying cost as Approach 1.
Time: O(n) typical, O(n^2) worst-case copying. Auxiliary space: O(h).

COMPLEXITY SUMMARY (n = nodes, h = tree height)
1. Recursive subtree strings: O(n) typical, potentially O(n^2) copying; O(h) stack.
2. Shared-string recursion: O(n) time; O(h) stack, excluding output.
3. Iterative frame stack: O(n) time; O(h) stack, worst-case O(n).
4. Recursive recurrence variant: same complexity profile as approach 1.

Recommended: Approach 2. It is easy to understand and appends to a single
string, avoiding repeated construction of entire subtree strings.
*/
