
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(!head) return nullptr;
        // if(!head->next) return nullptr;
        int L = 0;
        ListNode* curr = head;
        while(curr) {
            L++;
            curr = curr->next;
        }
        if(n == L) return  head->next;
        curr = head;

        for(int i=1; i<L-n; i++) {
            curr = curr->next;
        }

        if(curr->next) 
            curr->next = curr->next->next ;
        return head;
    }
};

/*
LeetCode 19: Remove Nth Node From End of List
All approaches: brute force -> optimal

LeetCode provides ListNode. Submit ONE Solution class at a time.
The classes below are named Solution1, Solution2, ... so they can coexist
in this reference file; rename the chosen class to Solution when submitting.

Problem:
Remove the nth node from the end and return the list's head.
Constraints guarantee 1 <= n <= list length.
*/

#include <vector>
using namespace std;

/*
Approach 1: Brute force — store node pointers in a vector
Idea:
- Store every node pointer in order.
- The target's zero-based index from the front is length - n.
- Reconnect the previous node to the node after the target.

Time:  O(L)
Space: O(L)

Special case: if target index is 0, the head is removed.
*/
class Solution1 {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        vector<ListNode*> nodes;
        ListNode* curr = head;

        while (curr != nullptr) {
            nodes.push_back(curr);
            curr = curr->next;
        }

        int target = static_cast<int>(nodes.size()) - n;

        if (target == 0) {
            ListNode* newHead = head->next;
            delete head;
            return newHead;
        }

        nodes[target - 1]->next = nodes[target]->next;
        delete nodes[target];
        return head;
    }
};

/*
Approach 2: Two passes — count length, then remove
Idea:
- First count L nodes.
- The target is (L - n) nodes from the beginning, using zero-based indexing.
- Walk to the node immediately before the target and unlink it.

Time:  O(L)
Space: O(1)

A dummy node makes deleting the head work naturally.
*/
class Solution2 {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(0, head);
        int length = 0;
        ListNode* curr = head;

        while (curr != nullptr) {
            ++length;
            curr = curr->next;
        }

        int steps = length - n;
        curr = &dummy;

        while (steps > 0) {
            curr = curr->next;
            --steps;
        }

        ListNode* target = curr->next;
        curr->next = target->next;
        delete target;

        return dummy.next;
    }
};

/*
Approach 3: One pass — fast and slow pointers (OPTIMAL)
Idea:
- Add a dummy node before head.
- Move fast n + 1 steps from dummy. This leaves fast n nodes ahead of slow.
- Move fast and slow together until fast reaches nullptr.
- slow is now immediately before the node to remove.

Time:  O(L)
Space: O(1)
This meets the follow-up: one traversal of the list.
*/
class Solution3 {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(0, head);
        ListNode* fast = &dummy;
        ListNode* slow = &dummy;

        int steps = n + 1;
        while (steps > 0) {
            fast = fast->next;
            --steps;
        }

        while (fast != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }

        ListNode* target = slow->next;
        slow->next = target->next;
        delete target;

        return dummy.next;
    }
};

/*
Approach 4: One pass — fast and slow pointers without dummy
Idea:
- Move fast n nodes from head.
- If fast is nullptr, the head itself is the target.
- Otherwise, advance fast and slow until fast->next is nullptr.
- slow is then the node before the target.

Time:  O(L)
Space: O(1)

This is also optimal, but has an extra head-removal case.
*/
class Solution4 {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* fast = head;
        ListNode* slow = head;

        int steps = n;
        while (steps > 0) {
            fast = fast->next;
            --steps;
        }

        if (fast == nullptr) {
            ListNode* newHead = head->next;
            delete head;
            return newHead;
        }

        while (fast->next != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }

        ListNode* target = slow->next;
        slow->next = target->next;
        delete target;

        return head;
    }
};

/*
Approach 5: Recursive — count nodes from the end while unwinding
Idea:
- Recursion reaches the end, then returns a counter representing position
  from the end.
- When the counter reaches n, remove that node.
- This is educational, but recursion uses O(L) call-stack space.

Time:  O(L)
Space: O(L)

The helper returns the updated head of each sublist and increments count
as recursion unwinds.
*/
class Solution5 {
private:
    ListNode* remove(ListNode* node, int n, int& count) {
        if (node == nullptr) {
            return nullptr;
        }

        node->next = remove(node->next, n, count);
        ++count;

        if (count == n) {
            ListNode* nextNode = node->next;
            delete node;
            return nextNode;
        }

        return node;
    }

public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int count = 0;
        return remove(head, n, count);
    }
};

/*
Complexity summary (L = number of nodes)

Approach                              Time     Auxiliary space
1. Vector of node pointers            O(L)     O(L)
2. Count length, then remove          O(L)     O(1)
3. Fast/slow + dummy (recommended)    O(L)     O(1)
4. Fast/slow without dummy            O(L)     O(1)
5. Recursive                          O(L)     O(L)

Recommended: Approach 3. It is one pass, O(1) auxiliary space, and the
dummy node handles removing the head without a separate special case.

IMPORTANT:
- LeetCode already declares ListNode, so do not paste another definition.
- To submit, copy one class and rename it from SolutionN to Solution.
- In LeetCode's environment, deleting the removed node is optional for
  correctness, but is good C++ memory hygiene.
*/
