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
    int pairSum(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        // get the mid of LL
        ListNode* previous=nullptr;
        while(fast && fast->next){
            previous = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode* newHead = slow;
        previous->next = nullptr;

        // Reverse the second half of LL
        ListNode* curr = newHead, *prev = nullptr, *nextNode = newHead->next;

        while(curr){
                 nextNode = curr->next;
                curr->next = prev;
                prev = curr;
                curr = nextNode;
        } 

        newHead = prev;

        int maxVal = -1;
        ListNode* tempI = head;
        ListNode* tempR = newHead;
        while(tempI && tempR){
            int twinSum = tempI->val + tempR->val;

            maxVal = max(twinSum, maxVal);

            tempI = tempI->next;
            tempR = tempR->next;
        }
        return maxVal;
    }
};