// Method 2 using binary lifting
// TC O(nlogn)
// (k >> j) & 1 => return 0 and 1
// k & (1 << j) => return 0 or 2^j


class TreeAncestor {
public:
    vector<vector<int>> ancestorTable;
    int rows;   // rows in ancestor table
    int cols; // cols in ancestor table
    TreeAncestor(int n, vector<int>& parent) {
        
        rows = n;
        cols = log2(n)+1; // exactly log2(n) but it comes float no,

        ancestorTable.resize(rows, vector<int> (cols, -1));

        // fill the 0th cols of ancestor table => immediate ancestor

        for(int i=0; i<n; i++){
            ancestorTable[i][0] = parent[i];
        }

        for(int j=1; j<cols; j++){

            for(int node=0; node<rows; node++){
                // recurrence relation of binary lifting => to build the ancestor table
                if (ancestorTable[node][j-1] != -1)
                    ancestorTable[node][j] = ancestorTable[ ancestorTable[node][j-1] ][j-1];
            }
        }
    }   
    
    int getKthAncestor(int node, int k) {
        
        for(int j=0; j<cols; j++){
            if(k & (1 << j)){ // jth bit of k is set => can take jump
                node = ancestorTable[node][j];

                if(node == -1){ // to check ancestor exist or not
                    return -1;
                }
            }
        }
        return node;
    }
};

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */
// method brute force TC(n*Q)
#include <iostream>
#include <vector>

class TreeAncestorBruteForce {
private:
    std::vector<int> parent;

public:
    // Constructor simply stores the parent array
    TreeAncestorBruteForce(const std::vector<int>& parent_array) {
        parent = parent_array;
    }
    
    // Function to retrieve the kth ancestor using Brute Force
    int getKthAncestor(int node, int k) {
        // Move up the tree step-by-step, k times
        for (int i = 0; i < k; ++i) {
            // Move to the immediate parent
            node = parent[node];
            
            // If we reach past the root node, return -1
            if (node == -1) {
                return -1;
            }
        }
        return node;
    }
};

int main() {
    // Example tree: Node 0 is root
    // Indices:                 0, 1, 2, 3, 4, 5, 6
    std::vector<int> parent = {-1, 0, 0, 1, 1, 2, 2};
    
    TreeAncestorBruteForce tree(parent);
    
    // Queries
    std::cout << "1st ancestor of node 3: " << tree.getKthAncestor(3, 1) << " (Expected: 1)\n";
    std::cout << "2nd ancestor of node 5: " << tree.getKthAncestor(5, 2) << " (Expected: 0)\n";
    std::cout << "3rd ancestor of node 6: " << tree.getKthAncestor(6, 3) << " (Expected: -1)\n";
    
    return 0;
}

#include <iostream>

// Definition for a binary tree node.
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinaryTreeAncestor {
private:
    Node* ancestor = nullptr;

    // Helper recursive function
    bool findAncestorDFS(Node* root, int target, int& k) {
        // Base case: empty node
        if (root == nullptr) return false;

        // If target node is found, start backtracking
        if (root->data == target) return true;

        // Search in left or right subtrees
        if (findAncestorDFS(root->left, target, k) || findAncestorDFS(root->right, target, k)) {
            // As we backtrack up the stack, decrease k
            k--;
            
            // When k hits 0, the current root is the kth ancestor
            if (k == 0) {
                ancestor = root;
            }
            return true;
        }
        return false;
    }

public:
    int getKthAncestor(Node* root, int target, int k) {
        ancestor = nullptr; // Reset for query
        findAncestorDFS(root, target, k);
        
        // If ancestor was found, return its data; otherwise return -1
        return (ancestor != nullptr) ? ancestor->data : -1;
    }
};

int main() {
    // Constructing the tree:
    //        1
    //       / \
    //      2   3
    //     / \
    //    4   5
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    BinaryTreeAncestor tree;

    std::cout << "1st ancestor of 5: " << tree.getKthAncestor(root, 5, 1) << " (Expected: 2)\n";
    std::cout << "2nd ancestor of 5: " << tree.getKthAncestor(root, 5, 2) << " (Expected: 1)\n";
    std::cout << "3rd ancestor of 4: " << tree.getKthAncestor(root, 4, 3) << " (Expected: -1)\n";

    return 0;
}
