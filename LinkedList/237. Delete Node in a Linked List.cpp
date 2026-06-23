class Solution {
public:
    void deleteNode(ListNode* node) {
        
        node->val = node->next->val;

        ListNode* prev = node;

        node->next = prev->next->next;
        
    }
};