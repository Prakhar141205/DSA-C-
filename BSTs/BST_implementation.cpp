#include <iostream>
#include <vector>

using namespace std;

class Node{
public:
    int val;
    Node* left;
    Node* right;

    Node(int d){
        val=d;
        left=right=nullptr;
    }

    
};

Node* insert(Node* root, int val){

    if(root == NULL) return new Node(val);
    if(root->val < val){
        root->right = insert(root->right, val);
    }else {
        root->left = insert(root->left, val);
    }
    return root;
}

Node* buildBST(vector<int> nodes){
        Node* root = NULL;

        for(int c : nodes){
            root = insert(root, c);
        }
        return root;
}

void inorder(Node* root){
    if(!root) return ;

    inorder(root->left);
    cout << root->val <<" ";
    inorder(root->right);
}



int main(){
    vector<int> nodes = {3, 2, 1, 5, 6, 4};

    Node* root = buildBST(nodes);
    inorder(root);
    return 0;
}