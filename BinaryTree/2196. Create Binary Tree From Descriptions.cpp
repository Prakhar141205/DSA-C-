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
//    Create a map: value -> TreeNode*
// Create a set: children

// FOR every description [parent, child, isLeft]

//     IF parent not in map
//         create TreeNode(parent)

//     IF child not in map
//         create TreeNode(child)

//     IF isLeft == 1
//         parent.left = child
//     ELSE
//         parent.right = child

//     insert child into children set

// END FOR


// FOR every node value present in map

//     IF node value is NOT in children set
//         return that node

// END FOR
    TreeNode* createBinaryTree(vector<vector<int>>& d) {
        // int node = getRootNode(descriptions);
        int n = d.size();

        unordered_map<int, TreeNode*> m; // node , pointer to node
        unordered_set<int> s;
        for(int i=0; i<n; i++){
            if(m.find(d[i][0]) == m.end()){
                m[d[i][0]] = new TreeNode(d[i][0]);
            }

            if(m.find(d[i][1]) == m.end()){
                m[d[i][1]] = new TreeNode(d[i][1]);
            }

            if(d[i][2] == 1){
                m[d[i][0]]->left = m[d[i][1]];
             }else{
                 m[d[i][0]]->right = m[d[i][1]];
            }
            s.insert(d[i][1]);
        }
        TreeNode* node;
        for(pair<int, TreeNode*> x: m){
            if(s.find(x.first) == s.end()){
                node = x.second;
                break;
            }
        }
        return node;
    }
};