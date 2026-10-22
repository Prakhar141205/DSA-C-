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
    ListNode* partition(ListNode* head, int x) {
        if(!head) return nullptr;

        ListNode *small = new ListNode(0);
        ListNode *large = new ListNode(0);
        ListNode *ts = small;
        ListNode *tl = large;

        while(head) {
            if(head -> val < x) {
                ts->next = head;
                ts = ts->next;
            }else {
                tl->next = head;
                tl = tl->next;
            }

            head = head->next;
        }

        ts->next = large->next;
        tl->next = nullptr;
        return small->next;

    }
};