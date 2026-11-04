
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


/*
    LeetCode 19. Remove Nth Node From End of List
    Language: C++17

    LeetCode provides ListNode. Do not redefine ListNode when submitting.

    Each approach is implemented in a separate class. Rename the selected
    class to Solution before submitting to LeetCode.

    The problem guarantees 1 <= n <= list length.
*/

#include <vector>
#include <stack>
using namespace std;

// -----------------------------------------------------------------------------
// Approach 1: Two-pass length calculation
// Technique: Count nodes, then move to the node immediately before the target.
//
// Time:  O(L)
// Space: O(1)
//
// Pass 1 obtains the list length L.
// The target's zero-based index from the front is L - n.
// A dummy node makes deleting the head work exactly like deleting any other
// node. The dummy itself is not returned.
// -----------------------------------------------------------------------------
class Solution_TwoPass {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int length = 0;

        for (ListNode* current = head; current != nullptr; current = current->next)
            ++length;

        ListNode dummy(0);
        dummy.next = head;

        // Stop at the node just before the one to remove.
        ListNode* previous = &dummy;
        int steps = length - n;

        while (steps-- > 0)
            previous = previous->next;

        ListNode* nodeToDelete = previous->next;
        previous->next = nodeToDelete->next;
        delete nodeToDelete;

        return dummy.next;
    }
};

// -----------------------------------------------------------------------------
// Approach 2: One-pass fast and slow pointers (RECOMMENDED)
// Technique: Two pointers + dummy node
//
// Time:  O(L)
// Space: O(1)
//
// Move fast n nodes ahead. Then move fast and slow together until fast reaches
// the last node. At that point slow is immediately before the target.
//
// Why it works:
//     fast is always n nodes ahead of slow. When fast reaches the final node,
//     slow is exactly n nodes before the end, i.e. just before the target.
// -----------------------------------------------------------------------------
class Solution_OnePassTwoPointers {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(0);
        dummy.next = head;

        ListNode* fast = &dummy;
        ListNode* slow = &dummy;

        // Establish a gap of n nodes between fast and slow.
        for (int i = 0; i < n; ++i)
            fast = fast->next;

        // Keep the gap while moving fast to the final node.
        while (fast->next != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }

        // slow is the node immediately before the node to remove.
        ListNode* nodeToDelete = slow->next;
        slow->next = nodeToDelete->next;
        delete nodeToDelete;

        return dummy.next;
    }
};

// -----------------------------------------------------------------------------
// Approach 3: Recursive traversal
// Technique: Recursion; return the distance from the end
//
// Time:  O(L)
// Space: O(L) recursion stack
//
// Each recursive call returns the current node's position counted from the
// end: last node returns 1, second-last returns 2, and so on.
// When the returned distance from the next node equals n, the current node
// is immediately before the target, so it bypasses and deletes that target.
//
// A pointer-to-pointer is not needed here because the dummy node handles the
// special case where the head itself must be removed.
// -----------------------------------------------------------------------------
class Solution_Recursive {
private:
    int removeFromEnd(ListNode* current, int n) {
        if (current == nullptr)
            return 0;

        int distance = removeFromEnd(current->next, n) + 1;

        if (distance == n + 1) {
            ListNode* nodeToDelete = current->next;
            current->next = nodeToDelete->next;
            delete nodeToDelete;
        }

        return distance;
    }

public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(0);
        dummy.next = head;
        removeFromEnd(&dummy, n);
        return dummy.next;
    }
};

// -----------------------------------------------------------------------------
// Approach 4: Stack of node pointers
// Technique: Stack
//
// Time:  O(L)
// Space: O(L)
//
// Push every node onto a stack. The top is the last node. Pop n nodes to reach
// the node immediately before the target. A dummy node is pushed first so
// removing the original head is handled uniformly.
//
// Note: The stack stores pointers; it does not copy the linked-list nodes.
// -----------------------------------------------------------------------------
class Solution_Stack {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(0);
        dummy.next = head;

        stack<ListNode*> nodes;
        nodes.push(&dummy);

        for (ListNode* current = head; current != nullptr; current = current->next)
            nodes.push(current);

        // Remove the target and all nodes after it from the stack.
        for (int i = 0; i < n; ++i)
            nodes.pop();

        // The new top is immediately before the target.
        ListNode* previous = nodes.top();
        ListNode* nodeToDelete = previous->next;

        previous->next = nodeToDelete->next;
        delete nodeToDelete;

        return dummy.next;
    }
};

// -----------------------------------------------------------------------------
// Approach 5: Store node pointers in a vector
// Technique: Vector / random access
//
// Time:  O(L)
// Space: O(L)
//
// The vector contains the original nodes in head-to-tail order.
// The target index from the front is L - n. Its predecessor can be found
// directly, with a separate case for deleting the head.
// -----------------------------------------------------------------------------
class Solution_Vector {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        vector<ListNode*> nodes;

        for (ListNode* current = head; current != nullptr; current = current->next)
            nodes.push_back(current);

        int targetIndex = static_cast<int>(nodes.size()) - n;
        ListNode* nodeToDelete = nodes[targetIndex];

        if (targetIndex == 0) {
            head = nodeToDelete->next;
        } else {
            nodes[targetIndex - 1]->next = nodeToDelete->next;
        }

        delete nodeToDelete;
        return head;
    }
};

/*
    DRY RUN — Approach 2 (one-pass two pointers)

    Input:
        head = 1 -> 2 -> 3 -> 4 -> 5
        n = 2

    Start:
        dummy -> 1 -> 2 -> 3 -> 4 -> 5
        fast = dummy
        slow = dummy

    Move fast n = 2 steps:
        fast: dummy -> 1 -> 2
        slow: dummy

    Move both until fast is the last node:
        fast = 3, slow = 1
        fast = 4, slow = 2
        fast = 5, slow = 3

    Now slow->next is 4, the 2nd node from the end.
    Bypass and delete it:
        slow->next = 5

    Output:
        1 -> 2 -> 3 -> 5

    EDGE CASE — remove the head:
        head = 1 -> 2, n = 2

        After moving fast two steps:
            fast = 2, slow = dummy

        fast is already the last node, so the loop does not run.
        slow->next is 1; bypass it and return dummy->next (node 2).

    COMPLEXITY SUMMARY:
        Two-pass length:       O(L) time, O(1) extra space
        One-pass pointers:     O(L) time, O(1) extra space
        Recursion:             O(L) time, O(L) call stack
        Stack:                 O(L) time, O(L) extra space
        Vector:                O(L) time, O(L) extra space

    RECOMMENDATION:
        Use Solution_OnePassTwoPointers for the follow-up requirement.
        It traverses the list once, uses O(1) extra space, and handles head
        deletion cleanly through the dummy node.

    MEMORY MANAGEMENT:
        Each implementation deletes the removed node with delete.
        This is appropriate for the standard LeetCode ListNode allocation
        model. The dummy node is a local stack object and is never deleted.
*/
