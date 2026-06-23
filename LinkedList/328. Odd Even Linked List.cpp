/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    typedef ListNode* ll ;
    ListNode* oddEvenList(ListNode* head) {
        if(!head) return head;

        ll evenStart = head->next;

        ll evenHead =  head->next;
        ll oddHead = head;

        while(evenHead && evenHead->next){
            oddHead->next = evenHead->next;
            evenHead->next = evenHead->next->next;

            oddHead = oddHead->next;
            evenHead = evenHead->next;

        }

        oddHead->next = evenStart;

        return head;
        
        
    }
};