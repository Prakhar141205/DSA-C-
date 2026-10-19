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
    int getSize(ListNode *head) {
        int ans = 0;
        ListNode *t = head;
        while(t) {
            ans += 1;

            t = t->next;
        }
        return ans;
    }
    ListNode* swapNodes(ListNode* head, int k) {
        if(!head ) return nullptr;
        if(!head->next ) return head;
        int n = getSize(head);
        
        ListNode *p1 = head;
        ListNode *p2 = head;

       for(int i=0; i<k-1; i++) {
            p1 = p1->next;
       }

       for(int i=0; i<n-k; i++) {
            p2 = p2->next;
       }

        int v = p1->val;
        p1->val = p2->val;
        p2->val = v ;
        return head;
    }
};