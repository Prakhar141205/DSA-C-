#include <vector>
using namespace std;

/*
    LeetCode 21. Merge Two Sorted Lists
    Language: C++17

    LeetCode provides the ListNode definition. Do not add another definition
    when submitting this file there.

    All approaches below splice/reuse the original list nodes, except where
    explicitly noted. Each class has a separate name; rename the selected
    class to Solution before submitting to LeetCode.

    Example:
        list1: 1 -> 2 -> 4
        list2: 1 -> 3 -> 4

        merged: 1 -> 1 -> 2 -> 3 -> 4 -> 4
*/

// -----------------------------------------------------------------------------
// Approach 1: Iterative merge using a dummy (sentinel) node
// Technique: Two pointers + dummy node
//
// Time:  O(n + m) - each node is visited and linked once.
// Space: O(1)     - only a few pointers; no new data nodes are allocated.
//
// This is the recommended approach: simple, iterative, and constant extra
// space. The dummy node is only a temporary anchor, not part of the result.
// -----------------------------------------------------------------------------
class Solution_IterativeDummy {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;

        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val <= list2->val) {
                tail->next = list1;
                list1 = list1->next;
            } else {
                tail->next = list2;
                list2 = list2->next;
            }

            tail = tail->next;
        }

        // At most one list still has nodes. Its remaining suffix is already
        // sorted, so attach the entire suffix in one operation.
        tail->next = (list1 != nullptr) ? list1 : list2;

        return dummy.next;
    }
};

// -----------------------------------------------------------------------------
// Approach 2: Recursive merge
// Technique: Recursion
//
// Time:  O(n + m)
// Space: O(n + m) call stack in the worst case.
//
// This is essentially the approach in the submitted code. At every call,
// choose the smaller head, and make its next pointer point to the merge of
// the remaining nodes. The base cases return the non-empty list directly.
// -----------------------------------------------------------------------------
class Solution_Recursive {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (list1 == nullptr) return list2;
        if (list2 == nullptr) return list1;

        if (list1->val <= list2->val) {
            list1->next = mergeTwoLists(list1->next, list2);
            return list1;
        }

        list2->next = mergeTwoLists(list1, list2->next);
        return list2;
    }
};

// -----------------------------------------------------------------------------
// Approach 3: Iterative merge without a dummy node
// Technique: Two pointers + explicit result head/tail
//
// Time:  O(n + m)
// Space: O(1)
//
// This avoids the sentinel node. The first selected node initializes the
// result head; after that, tail tracks the final node of the merged prefix.
// -----------------------------------------------------------------------------
class Solution_IterativeNoDummy {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (list1 == nullptr) return list2;
        if (list2 == nullptr) return list1;

        ListNode* head = nullptr;
        ListNode* tail = nullptr;

        // Select the first node separately so that head is initialized.
        if (list1->val <= list2->val) {
            head = tail = list1;
            list1 = list1->next;
        } else {
            head = tail = list2;
            list2 = list2->next;
        }

        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val <= list2->val) {
                tail->next = list1;
                list1 = list1->next;
            } else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }

        tail->next = (list1 != nullptr) ? list1 : list2;
        return head;
    }
};

// Correct vector-based implementation: keep each sorted pointer sequence
// separate, then merge their indices.
class Solution_VectorMerge {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        vector<ListNode*> a, b;

        for (ListNode* p = list1; p != nullptr; p = p->next)
            a.push_back(p);
        for (ListNode* p = list2; p != nullptr; p = p->next)
            b.push_back(p);

        vector<ListNode*> merged;
        merged.reserve(a.size() + b.size());

        size_t i = 0, j = 0;
        while (i < a.size() && j < b.size()) {
            if (a[i]->val <= b[j]->val)
                merged.push_back(a[i++]);
            else
                merged.push_back(b[j++]);
        }

        while (i < a.size()) merged.push_back(a[i++]);
        while (j < b.size()) merged.push_back(b[j++]);

        if (merged.empty()) return nullptr;

        // Reconnect the original nodes in the merged order.
        for (size_t k = 1; k < merged.size(); ++k)
            merged[k - 1]->next = merged[k];

        merged.back()->next = nullptr;
        return merged.front();
    }
};

/*
    The vector-based approach is included for learning, but it uses O(n + m)
    auxiliary space and is not preferable to the in-place iterative approach.

    Dry run for Approach 1:
        list1: 1 -> 2 -> 4
        list2: 1 -> 3 -> 4

        Compare 1 and 1: attach list1's 1
        Compare 2 and 1: attach list2's 1
        Compare 2 and 3: attach list1's 2
        Compare 4 and 3: attach list2's 3
        Compare 4 and 4: attach list1's 4 (<= keeps the merge stable)
        list1 is now empty; attach list2's remaining 4

        Result: 1 -> 1 -> 2 -> 3 -> 4 -> 4

    Correctness invariant for the iterative approaches:
        Before every comparison, the result chain contains the smallest
        already-processed nodes in sorted order, and tail points to its last
        node. The smaller current head is therefore the next smallest
        unprocessed node. Once one list ends, the other list's remaining
        suffix can be attached directly because it is already sorted.

    Review of the submitted recursive code:
        Your implementation is correct and accepted.
        - The two null checks are the correct base cases.
        - You choose the smaller head and recursively merge the remainder.
        - You reuse the existing nodes; you do not create replacement nodes.
        - When values are equal, choosing list2 (as your '<' condition does)
          is still correct. Using '<=' simply makes the tie preference explicit.
        Its worst-case recursion depth is n + m, so the iterative dummy-node
        solution avoids that call-stack cost.
*/
