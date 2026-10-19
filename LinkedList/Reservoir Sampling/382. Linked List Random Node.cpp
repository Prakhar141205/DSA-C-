// Using Reservoir Sampling

class Solution {
private:
    ListNode* head;
public:
    Solution(ListNode* head) {
        this->head = head;
    }
    
    int getRandom() {
        int count = 0, result;
        ListNode* curr = head;
        while (curr) {
            count++;
            if (rand() % count == 0) {
                result = curr->val;
            }
            curr = curr->next;
        }
        return result;
    }
};