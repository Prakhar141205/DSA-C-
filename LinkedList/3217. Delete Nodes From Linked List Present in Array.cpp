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
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        if(!head) return nullptr;
        unordered_set<int> st(begin(nums), end(nums));

        ListNode *curr = head;

        while(curr->next) {
            cout << curr->val << " ";
            if(st.find(curr->next->val) != st.end()) {
                
                curr->next = curr->next->next;
            }else 

                curr = curr->next;
        }

        if(st.find(head->val) != st.end()) {
            return head->next;
        } 

        return head;
    }
};