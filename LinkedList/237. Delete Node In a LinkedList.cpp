class Solution {
public:
    typedef ListNode* ll;

    void deleteNode(ListNode* node) {

        node->val = node->next->val;
        node->next = node->next->next;
        
    }
};


class Solution {
public:
    typedef ListNode* ll;

    void deleteNode(ListNode* node) {

        ll temp = node;

        while(temp->next->next) {
            temp->val = temp->next->val;
            temp = temp->next;
        }

        temp->val = temp->next->val;
        temp->next = nullptr;
        
    }
};