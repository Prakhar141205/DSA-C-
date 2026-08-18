
class Solution {
  public:
    Node *flattenBST(Node *root) {
       
       if(!root) return nullptr;
       
       Node* head = flattenBST(root->left);
       root->left = nullptr;
        root->right = flattenBST(root->right);
       
       if(head) {
           Node* temp = head;
           
           while(temp && temp->right) {
               temp = temp->right;
           }
           
           temp->right = root ;
       }else {
           head = root;
       }
        
        
       return head;
        
    }
};