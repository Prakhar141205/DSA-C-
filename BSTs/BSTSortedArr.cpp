#include <iostream>
#include <vector>

using namespace std;

class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node(int d){
        val = d;

        left = right = nullptr;
    }
};


void inorder(Node* root){
    if(!root) return;

    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

Node* helper(vector<int> arr, int st, int end){
    if(st > end) return nullptr;
    int mid = st + (end - st)/2;

    Node* root = new Node(arr[mid]);

    root->left = helper(arr, st, mid-1);
    root->right = helper(arr, mid+1, end);

    return root;
}

Node* buildBSTSortedArr(vector<int> arr){
    return helper(arr, 0, arr.size()-1);
}

int main(){
    vector<int> arr = {1, 3, 4, 5, 6, 7, 8};

    Node* root = buildBSTSortedArr(arr);

    inorder(root);


    return 0;
}