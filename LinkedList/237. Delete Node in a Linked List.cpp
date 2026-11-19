class Solution {
public:
    void deleteNode(ListNode* node) {
        
        node->val = node->next->val;

        ListNode* prev = node;

        node->next = prev->next->next;
        
    }
};


class Solution {
public:
    void deleteNode(ListNode* node) {
        
        ListNode* temp = node;
        
        while(temp->next->next) {
            temp->val = temp->next->val;
            temp = temp->next;
            cout << temp->val ;
        }
        
        temp->val = temp->next->val;
        temp->next = nullptr;
    }
};