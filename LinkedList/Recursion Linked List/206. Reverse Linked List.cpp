#include <bits/stdc++.h>
using namespace std;

/*
    LeetCode 206 - Reverse Linked List

    LeetCode supplies the ListNode definition. Do not duplicate it there.

    Approaches:
      1. Iterative three-pointer reversal
      2. Recursive suffix reversal (your approach)
      3. Recursive previous/current helper
      4. Stack of node pointers
      5. Vector of node pointers

    Each class is independent. Rename the chosen class to Solution.
*/


// 1. Iterative three-pointer reversal
// Data structure: linked-list pointers only.
// Time: O(n); Extra space: O(1).
class SolutionIterative {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;

        while (curr != nullptr) {
            ListNode* nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }

        return prev;
    }
};


// 2. Recursive suffix reversal (the approach in your submission)
// Data structure: recursion call stack.
// Time: O(n); Extra space: O(n).
class SolutionRecursive {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        ListNode* newHead = reverseList(head->next);

        head->next->next = head;
        head->next = nullptr;

        return newHead;
    }
};


// 3. Recursive helper with previous and current pointers
// Data structure: recursion call stack + list pointers.
// Time: O(n); Extra space: O(n).
// Recursive version of the iterative three-pointer technique.
class SolutionRecursiveAccumulator {
private:
    ListNode* reverseHelper(ListNode* prev, ListNode* curr) {
        if (curr == nullptr) return prev;

        ListNode* nextNode = curr->next;
        curr->next = prev;

        return reverseHelper(curr, nextNode);
    }

public:
    ListNode* reverseList(ListNode* head) {
        return reverseHelper(nullptr, head);
    }
};


// 4. Stack of node pointers
// Data structure: stack.
// Time: O(n); Extra space: O(n).
// Reuses existing nodes; does not allocate new ListNode objects.
class SolutionUsingStack {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr) return nullptr;

        stack<ListNode*> nodes;

        for (ListNode* curr = head; curr != nullptr; curr = curr->next) {
            nodes.push(curr);
        }

        ListNode* newHead = nodes.top();
        nodes.pop();

        ListNode* curr = newHead;

        while (!nodes.empty()) {
            curr->next = nodes.top();
            nodes.pop();
            curr = curr->next;
        }

        curr->next = nullptr;
        return newHead;
    }
};


// 5. Vector of node pointers
// Data structure: vector.
// Time: O(n); Extra space: O(n).
// Store addresses in traversal order, then reconnect them backwards.
class SolutionUsingVector {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr) return nullptr;

        vector<ListNode*> nodes;

        for (ListNode* curr = head; curr != nullptr; curr = curr->next) {
            nodes.push_back(curr);
        }

        for (int i = (int)nodes.size() - 1; i > 0; --i) {
            nodes[i]->next = nodes[i - 1];
        }

        nodes[0]->next = nullptr;
        return nodes.back();
    }
};


/*
    Dry run: 1 -> 2 -> 3 -> nullptr

    Iterative:
      Start: prev=null, curr=1
      Step 1: save 2; 1->next=null; prev=1; curr=2
      Step 2: save 3; 2->next=1;    prev=2; curr=3
      Step 3: save null; 3->next=2; prev=3; curr=null
      Return prev: 3 -> 2 -> 1 -> nullptr

    Your recursive approach:
      reverseList(1)
        reverseList(2)
          reverseList(3) returns 3
          3->next = 2; 2->next = null; return 3
        2->next = 1; 1->next = null; return 3
      Result: 3 -> 2 -> 1 -> nullptr

    Key details:
      - Save curr->next before reversing a link in the iterative approach.
      - Set the new tail's next to nullptr to avoid a cycle.
      - The algorithms reuse the original nodes.
      - Recursive approaches use O(n) call-stack space.

    Recommended:
      - Approach 1: best overall, O(n) time and O(1) extra space.
      - Approach 2: clean recursive solution and matches your code.
      - Approach 3: helps visualize recursion as pointer-state progression.
*/
