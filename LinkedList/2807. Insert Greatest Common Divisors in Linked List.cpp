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
    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        if(!head || !head->next) return head;

        ll currNode = head;
        ll nextNode = head->next;

        while(nextNode) {
            ll temp = new ListNode(__gcd(currNode->val, currNode->next->val));

            currNode->next = temp;
            temp->next = nextNode;

            currNode = nextNode;
            nextNode = nextNode->next;
        }
        return head;
    }
};

// Recursion
class Solution {
public:
    typedef ListNode* ll;
    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        if(!head || !head->next) return head;

            ll temp = insertGreatestCommonDivisors(head->next);

            ll gcdNode = new ListNode(__gcd(head->val, head->next->val));

            gcdNode->next = temp;
            head->next = gcdNode;


        
        return head;
    }
};

class Solution {
public:
    typedef ListNode* ll;
    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        if(!head || !head->next) return head;
            

            ll re_nxt = head->next;
            ll gcdNode = new ListNode(__gcd(head->val, head->next->val));

            gcdNode->next = re_nxt;
            head->next = gcdNode;

            insertGreatestCommonDivisors(gcdNode->next);
        return head;
    }
};