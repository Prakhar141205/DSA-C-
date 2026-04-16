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

void inorder(Node* root){ // O(n)
    if(!root) return ;

    inorder(root->left);
    cout << root->val <<" ";
    inorder(root->right);

    
}

// Search in Binary Search Tree 
// TC O(logn) in avg case
bool search(Node* root, int key){ // O(height) => O(logn)
    if(!root) return false;
    else if(root->val == key) return true;
    else if(root->val < key){
        return search(root->right, key);
    }else{
        return search(root->left, key);
    }
    return false;
}

Node* getInorderSuccessor(Node* root){  // left most node in the right subtree

    while(root != nullptr && root->left != nullptr){
        root = root->left;
    }
    return root;
}


// deleting the node in the BST
Node* deleteInBST(Node* root, int delNode){
    // step 1 => search the node to be deleted
    if(root == nullptr) return nullptr; 
    
    if(root->val < delNode){
        root->right = deleteInBST(root->right, delNode);
    }else if(root->val > delNode){
        root->left = deleteInBST(root->left, delNode);
    }else {// get the node to be deleted
        // 0 child and 1 child
        if(root->left == nullptr){
            Node* temp = root->right;
            delete root;
            return temp;
        }else if(root->right == nullptr){
            Node* temp = root->left;
            delete root;
            return temp;
        }else{ // two children

            Node* IS = getInorderSuccessor(root->right);
            root->val = IS->val;
            root->right = deleteInBST(root->right, IS->val);
        }
    }
    return root;
}


int main(){
    vector<int> nodes = {3, 2, 1, 5, 6, 4};

    Node* root = buildBST(nodes);
    inorder(root);
    cout << endl;
    deleteInBST(root, 1);
    inorder(root);
    cout << endl;
    deleteInBST(root, 2);
    inorder(root);

    cout << endl;
    deleteInBST(root, 5);
    inorder(root);
    cout << endl;
    return 0;
}