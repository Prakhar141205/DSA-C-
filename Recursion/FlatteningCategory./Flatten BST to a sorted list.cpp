
/********************************************************************* C++ ***********************************************************************************/
//T.C : O(n^2)
//S.C : Auxiliary Space is O(1) and Stack Space due to recursion is O(n)
class Solution
{
public:
    Node *flattenBST(Node *root) {
        if(!root) {
            return NULL;
        }
        
        Node* head   = flattenBST(root->left);
        root->left = NULL;
        root->right  = flattenBST(root->right);
        
        if (head) {
            Node *temp = head;
            while (temp->right) {
                temp = temp->right;
            }
            temp->right = root;
        } else {
            // If head is NULL, root becomes the head
            head = root;
        }
        
        return head;
    }
};

//Approach-2
//T.C : O(n)
//S.C : Auxiliary Space is O(1) and Stack Space due to recursion is O(n)
class Solution
{
public:
    Node* prev = NULL;
    Node *flattenBST(Node *root) {
        
        if(!root) {
            return NULL;
        }
        
        Node* head = flattenBST(root->left); //Trust
        root->left = NULL;
        if(prev) {
            prev->right = root;
            prev = root;
        } else {
            prev = root;
        }
        root->right = flattenBST(root->right); //Trust

        if(head == NULL) {
            return root;
        }

        return head;
        
    }
};