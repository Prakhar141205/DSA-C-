/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    typedef ListNode* ll ;
    ListNode *detectCycle(ListNode *head) {
        
        if(!head || !head->next) return nullptr;

        ll slow = head;
        ll fast = head;

        while(fast && fast->next)  {
            slow = slow->next;
            fast = fast->next->next;

            if(slow == fast) break;
        }

        if(slow != fast) return nullptr;

        ll p = head;

        while(p != slow) {
            p = p->next;
            slow = slow->next;
        }
        
        return p;
    }
};