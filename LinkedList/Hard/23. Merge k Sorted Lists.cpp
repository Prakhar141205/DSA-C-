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
    typedef ListNode* ll; 

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto lambda = [] (ll node1, ll node2) {
            return node1->val > node2->val;
        };

        priority_queue<ll, vector<ll>, decltype(lambda)> pq(lambda);

        for(auto& node : lists){
            if(node) {
                pq.push(node);
            }
        }

        if(pq.empty()) return nullptr;

        ll head = pq.top();
        pq.pop();

        if(head->next){
            pq.push(head->next);
        }

        ll tail = head;
        while(!pq.empty()){
            ll curr = pq.top();
            pq.pop();

            tail->next = curr;
            tail = tail->next;

            if(curr->next) {
                pq.push(curr->next);
            }
        }

        return head;
    }
};