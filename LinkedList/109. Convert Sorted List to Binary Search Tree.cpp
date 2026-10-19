
class Solution {
public:
    TreeNode *solve(vector<int>& nodes, int st, int end) {
        if(st > end) return nullptr;

        int m  = st + (end - st) / 2;

        TreeNode* root = new TreeNode(nodes[m]);

        root->left = solve(nodes, st, m-1);
        root->right = solve(nodes, m+1, end);

        return root;
    }
    TreeNode* sortedListToBST(ListNode* head) {
        if(!head) return nullptr;
        ListNode *temp = head;

        vector<int> nodes;

        while(temp)  {
            nodes.push_back(temp->val);
            temp = temp->next;
        }

        return solve(nodes, 0, nodes.size() - 1) ;
    }
};


// constant space solutions

class Solution {
public:
    TreeNode *solve(ListNode* head) {
        if(!head) return nullptr;
        if(!head->next) return new TreeNode(head->val);
        // finding the middle nodes;
        ListNode *slow = head;
        ListNode *fast = head;
        ListNode *prev = nullptr;
        while(fast && fast->next)  {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        TreeNode* root = new TreeNode(slow->val);
        prev->next = nullptr; // break the connection 

        root->left = solve(head);
        root->right = solve(slow->next);

        return root;
    }
    TreeNode* sortedListToBST(ListNode* head) {
        if(!head) return nullptr;
        if(!head->next) return new TreeNode(head->val);
        
        return solve(head) ;
    }
};