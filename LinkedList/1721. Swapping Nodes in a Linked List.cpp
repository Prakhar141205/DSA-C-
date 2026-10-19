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
    ListNode* swapNodes(ListNode* head, int k) {
        if(!head) return nullptr;
        if(!head->next) return head;
        vector<int> nodes;
        ListNode *temp = head;

        while(temp) {
            nodes.push_back(temp->val);
            temp = temp->next;
        }

        int i = k-1;
        int t = nodes.size() ;
        int j  = t - k;

        swap(nodes[i], nodes[j]);
       
        temp = head ;

        for(int i=0; i<t; i++) {
            temp->val = nodes[i];
            temp = temp->next;
        }
        return head;
    }
};