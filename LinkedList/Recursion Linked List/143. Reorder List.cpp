

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
    ListNode* reverseLL(ListNode* head) {
        if(!head or !head->next) return head;

        ListNode* lastNode = reverseLL(head->next);
        head->next->next = head;
        head->next = nullptr;

        return lastNode;
    }
    void reorderList(ListNode* head) {
        if(!head or !head->next) return;

        ListNode* slow = head;
        ListNode* fast = head;

        while(fast and fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode* rev = reverseLL(slow);

        ListNode* curr = head;

        while(rev->next) {
            ListNode* tempcurr = curr->next;
            curr->next = rev;

            ListNode* temprev = rev->next;
            rev->next = tempcurr;
            curr = tempcurr;
            rev = temprev;

        }

        return;
    }

};
/*
    LeetCode 143. Reorder List
    Language: C++17

    LeetCode provides ListNode. Do not redefine it when submitting.

    Required transformation:
        L0 -> L1 -> L2 -> ... -> Ln
        becomes
        L0 -> Ln -> L1 -> Ln-1 -> L2 -> Ln-2 -> ...

    Node values must not be changed. All approaches below rearrange node links.

    Each approach is a separate class. Rename the chosen class to Solution.
*/

#include <vector>
#include <deque>
#include <stack>
using namespace std;

// -----------------------------------------------------------------------------
// Approach 1: Find middle + reverse second half + merge alternately
// Technique: Fast/slow pointers + in-place reversal + pointer weaving
//
// Time:  O(n)
// Space: O(1)
//
// This is the standard optimal solution.
//
// Steps:
//   1. Find the end of the first half.
//   2. Split the list into two halves.
//   3. Reverse the second half.
//   4. Alternately take one node from each half.
// -----------------------------------------------------------------------------
class Solution_Optimal {
private:
    ListNode* reverseList(ListNode* head) {
        ListNode* previous = nullptr;
        ListNode* current = head;

        while (current != nullptr) {
            ListNode* nextNode = current->next;
            current->next = previous;
            previous = current;
            current = nextNode;
        }

        return previous;
    }

public:
    void reorderList(ListNode* head) {
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
            return;

        // Find the final node of the first half.
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // Split the list so that the two halves are independent.
        ListNode* second = slow->next;
        slow->next = nullptr;

        // Reverse the second half.
        second = reverseList(second);

        // Weave the two halves together.
        ListNode* first = head;

        while (second != nullptr) {
            ListNode* firstNext = first->next;
            ListNode* secondNext = second->next;

            first->next = second;
            second->next = firstNext;

            first = firstNext;
            second = secondNext;
        }
    }
};

// -----------------------------------------------------------------------------
// Approach 2: Store all node pointers in a vector, then use two ends
// Technique: Vector + two pointers
//
// Time:  O(n)
// Space: O(n)
//
// The vector gives direct access to the first and last remaining nodes.
// We only change next pointers; node values are never modified.
// -----------------------------------------------------------------------------
class Solution_VectorTwoPointers {
public:
    void reorderList(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return;

        vector<ListNode*> nodes;

        for (ListNode* current = head; current != nullptr; current = current->next)
            nodes.push_back(current);

        int left = 0;
        int right = static_cast<int>(nodes.size()) - 1;

        while (left < right) {
            nodes[left]->next = nodes[right];
            ++left;

            // If the pointers meet, the middle node is already in place.
            if (left == right)
                break;

            nodes[right]->next = nodes[left];
            --right;
        }

        // Terminate the reordered list to avoid a cycle.
        nodes[left]->next = nullptr;
    }
};

// -----------------------------------------------------------------------------
// Approach 3: Deque of node pointers
// Technique: Deque + alternating front/back extraction
//
// Time:  O(n)
// Space: O(n)
//
// Repeatedly take the front node, then the back node, and connect them.
// A deque makes both-end removal O(1).
// -----------------------------------------------------------------------------
class Solution_Deque {
public:
    void reorderList(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return;

        deque<ListNode*> nodes;

        for (ListNode* current = head; current != nullptr; current = current->next)
            nodes.push_back(current);

        ListNode dummy(0);
        ListNode* tail = &dummy;
        bool takeFront = true;

        while (!nodes.empty()) {
            ListNode* chosen;

            if (takeFront) {
                chosen = nodes.front();
                nodes.pop_front();
            } else {
                chosen = nodes.back();
                nodes.pop_back();
            }

            tail->next = chosen;
            tail = chosen;
            takeFront = !takeFront;
        }

        tail->next = nullptr;
    }
};

// -----------------------------------------------------------------------------
// Approach 4: Stack the second half
// Technique: Slow/fast pointers + stack
//
// Time:  O(n)
// Space: O(n)
//
// Push the second half's nodes onto a stack. Then walk the first half and
// insert one popped node after each first-half node.
// -----------------------------------------------------------------------------
class Solution_Stack {
public:
    void reorderList(ListNode* head) {
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
            return;

        ListNode* slow = head;
        ListNode* fast = head;

        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        stack<ListNode*> secondHalf;
        ListNode* current = slow->next;
        slow->next = nullptr;

        while (current != nullptr) {
            stackHalfPush(secondHalf, current);
            current = current->next;
        }

        // Rebuild the list by inserting nodes from the stack in reverse order.
        current = head;

        while (!secondHalf.empty()) {
            ListNode* inserted = secondHalf.top();
            secondHalf.pop();

            ListNode* nextFirst = current->next;
            current->next = inserted;
            inserted->next = nextFirst;

            current = nextFirst;
        }

        // The last node in the first half may be the middle node.
        // It is already terminated because we split at slow.
    }

private:
    void stackHalfPush(stack<ListNode*>& nodes, ListNode* node) {
        nodes.push(node);
    }
};

// -----------------------------------------------------------------------------
// Approach 5: Recursive front/back weaving
// Technique: Recursion + front pointer passed by reference
//
// Time:  O(n)
// Space: O(n) recursion stack
//
// Recursion reaches the tail. While unwinding, it places tail-side nodes
// between nodes reached by the front pointer.
//
// This is included as a recursion exercise; the optimal iterative solution
// avoids the O(n) call stack.
// -----------------------------------------------------------------------------
class Solution_Recursive {
private:
    bool weave(ListNode*& front, ListNode* back) {
        if (back == nullptr)
            return true;

        if (!weave(front, back->next))
            return false;

        // If front has met back, or has crossed it, all pairs are processed.
        if (front == back || front->next == back) {
            back->next = nullptr;
            return false;
        }

        ListNode* nextFront = front->next;
        front->next = back;
        back->next = nextFront;
        front = nextFront;

        return true;
    }

public:
    void reorderList(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return;

        ListNode* front = head;
        weave(front, head);
    }
};

/*
    DRY RUN — Approach 1

    Input:
        1 -> 2 -> 3 -> 4 -> 5

    Step 1: Find the end of the first half.
        slow = 3
        first half:  1 -> 2 -> 3
        second half: 4 -> 5

    Step 2: Split and reverse the second half.
        first:  1 -> 2 -> 3
        second: 5 -> 4

    Step 3: Weave one node from each half.

        Take 1, then 5:
            1 -> 5 -> 2 -> 3
        Take 2, then 4:
            1 -> 5 -> 2 -> 4 -> 3

    Output:
        1 -> 5 -> 2 -> 4 -> 3

    EVEN-LENGTH EXAMPLE:
        Input: 1 -> 2 -> 3 -> 4

        First half:  1 -> 2
        Second half: 3 -> 4
        Reversed:    4 -> 3
        Weave:       1 -> 4 -> 2 -> 3

    WHY THE OPTIMAL APPROACH WORKS:
        The first half contains the nodes in forward order:
            L0, L1, L2, ...
        Reversing the second half gives the remaining nodes in the required
        backward order:
            Ln, Ln-1, Ln-2, ...
        Alternately linking one node from each sequence produces exactly
        the required pattern.

    COMPLEXITY SUMMARY:
        Find middle + reverse + weave: O(n) time, O(1) space
        Vector + two ends:             O(n) time, O(n) space
        Deque:                         O(n) time, O(n) space
        Stack second half:             O(n) time, O(n) space
        Recursive weaving:             O(n) time, O(n) call stack

    IMPORTANT:
        - Node values are never changed.
        - The optimal solution explicitly splits the list before reversing.
        - The final link must be null; otherwise the reordered list may
          accidentally contain a cycle.
*/
