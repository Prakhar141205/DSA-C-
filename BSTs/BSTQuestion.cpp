#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Node{
public:
    int val;

    Node* left;
    Node* right;

    Node(int d){
        val = d;
        left = right = nullptr;
    }
};
Node* insert(Node* root , int val){
    if(root == nullptr){
        return new Node(val);
    }else if(root->val < val){
        root->right = insert(root->right, val);
    }else{
        root->left = insert(root->left, val);
    }

    return root;
}
Node* buildBST(vector<int> nodes){
    Node* root = nullptr;

    for(int c : nodes){
        root = insert(root, c);
    }
    return root;

}

void inorder(Node* root){
    if(!root) return ;

    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

// Validate BST 
bool helper(Node* root, Node* min, Node* max){
    if(!root) return true;

    if(min != nullptr && min->val >= root->val){
        return false;
    }

    if(max != nullptr && max->val <= root->val) return false;

    return helper(root->left, min, root)
            && helper(root->right, root, max);
}

bool validateBST(Node* root){
    if(!root) return true;
    Node* min = nullptr;
    Node* max = nullptr;
    return helper(root, min, max);
}


//  Minimum difference between the nodes of the BST

Node* previous = nullptr;

int minDiff(Node* root){

    
    if(root == nullptr){
        return INT_MAX;
    }
    int ans = INT_MAX;

    if(root->left != nullptr){
        int leftMin = minDiff(root->left);
        ans = min(ans, leftMin);

    }

    if(previous != nullptr){
        ans = min(ans,root->val - previous->val);

    }

    previous  = root;

    if(root->right != nullptr){
        int rightMin = minDiff(root->right);

        ans = min(rightMin, ans);
    }
    return ans;
}

// Kth Smallest in BST
int prevOrder = 0;
int KthSmallest(Node* root, int k){
    if(!root) return -1;

    if(root->left != nullptr){
        int leftAns = KthSmallest(root->left, k);
        return leftAns;
    }

    if(prevOrder + 1 == k){
        return root->val;
    }

    prevOrder += 1;

    if(root->right != nullptr){
        int rightAns = KthSmallest(root->right, k);
        return rightAns;
    }

    return -1;
}


// LCA in BST

Node* LCAInBST(Node* root, Node* p, Node* q){
    if(!root ) return nullptr;

    if(root->val > p->val && root->val < q->val){
        return LCAInBST(root->left, p, q);
    }else if(root->val < p->val && root->val < q->val){
        return LCAInBST(root->right, p, q);
    }else{
        return root;
    }

}
int main(){
    vector<int> nodes = {1, 2, 6 ,4,3 , 45, 323};

    Node* root = buildBST(nodes);

    inorder(root);

    // cout << validateBST(root);

    cout << KthSmallest(root, 3);
    return 0;
}