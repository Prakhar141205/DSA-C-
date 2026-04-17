#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Node{
public:
    int val;
    Node* left;
    Node* right;

    Node(int val){
        this->val = val;
        left = right = nullptr;
    }
};

static int idx = -1;
Node* buildTree(vector<int> nodes){
    idx++;
    if(nodes[idx] == -1){
        return nullptr;
    }

    Node* newNode = new Node(nodes[idx]);
    newNode->left = buildTree(nodes);
    newNode->right = buildTree(nodes);

    return newNode;
}

// Preorder
void preorder(Node* root){
    if(!root ) return;

    cout << root->val<<" ";
    preorder(root->left);
    preorder(root->right);
}

// Inorder
void inorder(Node* root){
    if(!root) return ;

    inorder(root->left);
    cout << root->val <<" ";
    inorder(root->right);
}

// Postorder
void postorder(Node* root){
    if(!root) return ;

    postorder(root->left);
    postorder(root->right);
    cout << root->val << " ";
}

void printAllPaths(Node* root, string path,  vector<string> &ans){
    
    if(root->left == nullptr && root->right == nullptr) {
       ans.push_back(path);
        return;
    }

    if(root->left) printAllPaths(root->left, path + to_string(root->val), ans);
    if(root->right) printAllPaths(root->right, path + to_string(root->val), ans);
}

// level Order Traversal Normal
void levelOrderTraversal(Node* root){
    queue<Node*> q;

    q.push(root);

    while(!q.empty()){
        Node* curr = q.front();
        cout << curr->val;
        q.pop();

        if(curr->left) q.push(curr->left);
        if(curr->right) q.push(curr->right);
    }
}

// Level order traversal level wise print using null pointer as a delimiter
void levelOrderTraversalLevelWise1(Node* root){
    queue<Node*> q;

    q.push(root);
    q.push(nullptr);

    while(!q.empty()){
        Node* curr = q.front();
        q.pop();
        if(curr == nullptr){
            if(q.empty()){
                break;
            }else{
                cout << endl;
                q.push(nullptr);

            }
        }else{ // curr != null
        
        cout << curr->val << " ";
        if(curr->left) q.push(curr->left);
        if(curr->right) q.push(curr->right);
        }
    }
}

// level Order Traversal usign for loop
void levelOrderTraversalLevelWise2(Node* root){
    queue<Node*> q;

    q.push(root);

    while(!q.empty()){
        int n = q.size();
        
        for(int i=0; i<n; i++){
            Node* curr = q.front();
            cout << curr->val << " ";
            q.pop();

            if(curr->left) q.push(curr->left);
            if(curr->right) q.push(curr->right);
        }
   }
}

// height of the binary tree recursive
int heightBinaryTree(Node* root){
    if(!root) return 0;

    int leftHeight = heightBinaryTree(root->left);
    int rightHeight = heightBinaryTree(root->right);

    return max(leftHeight, rightHeight) + 1 ;
}

// count number of nodes

int countNodes(Node* root){
    if(!root) return 0;

    int leftCount = countNodes(root->left);
    int rightCount = countNodes(root->right);

    return leftCount + rightCount + 1;
}

// check the tree are identical or not
bool isIdentical(Node* p, Node* q){
    if(p == nullptr || q == nullptr) return p == q;

    return isIdentical(p->left, q->left)
            && isIdentical(p->right, q->right)
            && p->val == q->val;
}

int sumNodes(Node* root){
    if(!root) return 0;
    
    return sumNodes(root->left) + sumNodes(root->right) + root->val;
}

// Diameter of the Binary Tree
int dia = 0;

int diamter(Node* root){
    if(!root) return 0;
    int leftHeight = diameter(root->left);
    int rightHeight = diameter(root-right);
    ans = max(ans, leftHeight+rightHeight);
    return  ans;
}

// diameter of a binary tree using pair
pair<int, int> diam(Node* root){
    if(root == nullptr) return {0,0};
    pair<int, int> leftInfo = diam(root->left);
    pair<int, int> rightInfo = diam(root->right);

    int currDiam = leftInfo.second + rightInfo.second;
    int finalDiam = max(currDiam, leftInfo.first+rightInfo.first);
    int finalHeight = max(leftInfo.first , rightInfo.first) + 1;

    return {finalDiam, finalHeight};
}

// Subtree of another tree

bool isSubTree(Node* root, Node* subRoot){
    if(root == nullptr || subRoot == nullptr) return root == subRoot;

    if(root->val == subRoot->val && isIdentical(root, subRoot)){
        return true;
    }

    return isSubTree(root->left, subRoot->left)
            || isSubTree(root->right, subRoot-right);
}
int main(){
    vector<int> nodes = {1, 2, 4, -1, -1, 5, -1, -1, 3, -1, 6, -1, -1};

    Node* root = buildTree(nodes);

    cout << heightBinaryTree(root);
    cout << endl;

    return 0;
}