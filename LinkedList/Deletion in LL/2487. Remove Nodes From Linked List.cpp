/*
    LeetCode 2487. Remove Nodes From Linked List
    Language: C++17
    LeetCode provides ListNode; do not redefine it when submitting.
    Remove a node only if a STRICTLY greater value exists to its right.
    Rename the selected approach class to Solution.
*/
#include <vector>
#include <stack>
using namespace std;

// Approach 1: Monotonic stack of node pointers
// Time O(n), space O(n). Equal values are retained by popping only on '<'.
class Solution_MonotonicStack {
public:
    ListNode* removeNodes(ListNode* head) {
        vector<ListNode*> st;
        for (ListNode* current = head; current != nullptr; current = current->next) {
            while (!st.empty() && st.back()->val < current->val)
                st.pop_back();
            st.push_back(current);
        }

        if (st.empty()) return nullptr;
        for (size_t i = 1; i < st.size(); ++i)
            st[i - 1]->next = st[i];
        st.back()->next = nullptr;
        return st.front();
    }
};

// Approach 2: Reverse, keep suffix maximums, reverse back
// Time O(n), space O(1). Recommended optimal approach.
class Solution_ReverseAndMax {
private:
    ListNode* reverseList(ListNode* node) {
        ListNode* previous = nullptr;
        while (node != nullptr) {
            ListNode* nextNode = node->next;
            node->next = previous;
            previous = node;
            node = nextNode;
        }
        return previous;
    }

public:
    ListNode* removeNodes(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;

        ListNode* reversed = reverseList(head);
        int maxSoFar = reversed->val;
        ListNode* previous = reversed;
        ListNode* current = reversed->next;

        while (current != nullptr) {
            if (current->val < maxSoFar) {
                previous->next = current->next;
                current = previous->next;
            } else {
                maxSoFar = current->val;
                previous = current;
                current = current->next;
            }
        }
        return reverseList(reversed);
    }
};

// Approach 3: Recursive suffix filtering
// Time O(n), space O(n) recursion stack.
class Solution_Recursive {
public:
    ListNode* removeNodes(ListNode* head) {
        if (head == nullptr) return nullptr;

        head->next = removeNodes(head->next);

        // The head of the filtered suffix is its maximum value.
        if (head->next != nullptr && head->val < head->next->val)
            return head->next;

        return head;
    }
};

// Approach 4: Vector of node pointers + right-to-left maximum
// Time O(n), space O(n).
class Solution_VectorSuffixMaximum {
public:
    ListNode* removeNodes(ListNode* head) {
        vector<ListNode*> nodes;
        for (ListNode* current = head; current != nullptr; current = current->next)
            nodes.push_back(current);

        vector<ListNode*> kept;
        int maxSoFar = -1; // Constraints: node values are at least 1.
        for (int i = static_cast<int>(nodes.size()) - 1; i >= 0; --i) {
            if (nodes[i]->val >= maxSoFar) {
                kept.push_back(nodes[i]);
                maxSoFar = nodes[i]->val;
            }
        }

        if (kept.empty()) return nullptr;

        // kept is right-to-left; relink it back into original order.
        for (int i = static_cast<int>(kept.size()) - 1; i > 0; --i)
            kept[i]->next = kept[i - 1];
        kept[0]->next = nullptr;
        return kept.back();
    }
};

// Approach 5: std::stack of pointers + reconstruction
// Time O(n), space O(n). Demonstrates the standard stack container.
class Solution_StdStack {
public:
    ListNode* removeNodes(ListNode* head) {
        stack<ListNode*> st;
        for (ListNode* current = head; current != nullptr; current = current->next) {
            while (!st.empty() && st.top()->val < current->val)
                st.pop();
            st.push(current);
        }

        vector<ListNode*> kept;
        while (!st.empty()) {
            kept.push_back(st.top());
            st.pop();
        }
        if (kept.empty()) return nullptr;

        for (int i = static_cast<int>(kept.size()) - 1; i > 0; --i)
            kept[i]->next = kept[i - 1];
        kept[0]->next = nullptr;
        return kept.back();
    }
};

/*
DRY RUN — Approach 2: Reverse + running maximum

Input:
    5 -> 2 -> 13 -> 3 -> 8

Reverse:
    8 -> 3 -> 13 -> 2 -> 5

Scan the reversed list:
    current = 8: keep; maxSoFar = 8
    current = 3: 3 < 8, remove
    current = 13: keep; maxSoFar = 13
    current = 2: 2 < 13, remove
    current = 5: 5 < 13, remove

Survivors in reversed order:
    8 -> 13

Reverse survivors:
    13 -> 8

Output:
    [13, 8]

EQUAL VALUES:
    Input: 1 -> 1 -> 1 -> 1
    Every value equals maxSoFar. Since removal uses '<' and not '<=',
    all nodes remain.

RECURSIVE APPROACH LOGIC:
    First recursively filter the suffix. Its returned head is the maximum
    node of that suffix. If the current node is smaller than that head,
    a greater value exists to its right, so skip the current node.
    Otherwise retain it.

COMPLEXITIES:
    1. Monotonic stack (vector): O(n) time, O(n) space
    2. Reverse + maximum:         O(n) time, O(1) space
    3. Recursion:                 O(n) time, O(n) call stack
    4. Vector suffix maximum:     O(n) time, O(n) space
    5. std::stack:                O(n) time, O(n) space

RECOMMENDATION:
    Approach 2 is optimal for auxiliary space.
    Approach 3 is useful for understanding recursion.
    Approaches 1 and 5 are useful for monotonic-stack practice.

All approaches relink original nodes; they do not change node values.
*/
