/*
    LeetCode 1669. Merge In Between Linked Lists
    Language: C++17

    LeetCode supplies the ListNode definition. Do not redefine it when
    submitting this file.

    Given:
        list1, indices a and b, and list2
    Replace list1[a..b] (inclusive) with the complete list2.

    All approaches below reuse and relink existing nodes. Each approach is
    placed in a separate class; rename the selected class to Solution.
*/

#include <vector>
using namespace std;

// -----------------------------------------------------------------------------
// Approach 1: Direct pointer splicing (RECOMMENDED)
// Technique: Pointer traversal + in-place linked-list splice
//
// Time:  O(n + m) worst case
// Space: O(1)
//
// Find:
//   beforeA = node at index a - 1
//   afterB  = node at index b + 1
//   tail2   = last node of list2
//
// Then connect:
//   beforeA -> list2 head
//   list2 tail -> afterB
//
// The removed nodes are simply detached from the resulting chain.
// -----------------------------------------------------------------------------
class Solution_DirectSplicing {
public:
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        ListNode* beforeA = list1;

        // Move to index a - 1.
        for (int i = 0; i < a - 1; ++i)
            beforeA = beforeA->next;

        // Move to index b + 1, the first node that must remain after list2.
        ListNode* afterB = beforeA;
        for (int i = 0; i < b - a + 2; ++i)
            afterB = afterB->next;

        // Find the tail of list2.
        ListNode* tail2 = list2;
        while (tail2->next != nullptr)
            tail2 = tail2->next;

        // Splice list2 into list1.
        beforeA->next = list2;
        tail2->next = afterB;

        return list1;
    }
};

// -----------------------------------------------------------------------------
// Approach 2: One traversal of list1, then one traversal of list2
// Technique: Single cursor + state-based pointer capture
//
// Time:  O(n + m)
// Space: O(1)
//
// This version scans list1 once and records the two boundary nodes. It then
// finds list2's tail and performs the same two pointer rewrites.
// -----------------------------------------------------------------------------
class Solution_SingleCursor {
public:
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        ListNode* current = list1;
        ListNode* beforeA = nullptr;
        ListNode* afterB = nullptr;

        int index = 0;
        while (current != nullptr) {
            if (index == a - 1)
                beforeA = current;

            if (index == b + 1) {
                afterB = current;
                break;
            }

            current = current->next;
            ++index;
        }

        ListNode* tail2 = list2;
        while (tail2->next != nullptr)
            tail2 = tail2->next;

        beforeA->next = list2;
        tail2->next = afterB;

        return list1;
    }
};

// -----------------------------------------------------------------------------
// Approach 3: Store list1 node addresses in a vector
// Technique: Vector / direct index lookup
//
// Time:  O(n + m)
// Space: O(n) for the vector
//
// The vector allows direct access to list1[a - 1] and list1[b + 1].
// This is easier to visualize with indices, but wastes auxiliary memory
// compared with direct pointer traversal.
// -----------------------------------------------------------------------------
class Solution_VectorIndexing {
public:
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        vector<ListNode*> nodes;

        for (ListNode* current = list1; current != nullptr; current = current->next)
            nodes.push_back(current);

        ListNode* beforeA = nodes[a - 1];
        ListNode* afterB = nodes[b + 1];

        ListNode* tail2 = list2;
        while (tail2->next != nullptr)
            tail2 = tail2->next;

        beforeA->next = list2;
        tail2->next = afterB;

        return list1;
    }
};

/*
    DRY RUN — Approach 1

    list1:
        index:  0   1   2   3   4   5
                10 -> 1 -> 13 -> 6 -> 9 -> 5

    a = 3, b = 4
    list2 = 1000000 -> 1000001 -> 1000002

    1. beforeA is the node at index a - 1 = 2:
           beforeA = 13

    2. afterB is the node at index b + 1 = 5:
           afterB = 5

    3. Find the tail of list2:
           tail2 = 1000002

    4. Rewire exactly two links:
           beforeA->next = list2
           tail2->next = afterB

    Result:
        10 -> 1 -> 13 -> 1000000 -> 1000001 -> 1000002 -> 5

    WHY THE OFFSET IS b - a + 2:
        Start at index a - 1. To reach index b + 1, move:
            (b + 1) - (a - 1) = b - a + 2
        next pointers.

    REVIEW OF YOUR ACCEPTED CODE:
        Your pointer logic is correct:
        - temp stops at index a - 1.
        - curr advances to index b + 1.
        - temp->next attaches list2.
        - the while loop finds list2's tail.
        - the tail is connected to curr.

        Improvements:
        1. Remove the cout statement. LeetCode does not need debug output.
        2. Rename temp/curr to beforeA/afterB for clarity.
        3. Your loop `i <= b-a+1` performs b-a+2 moves, which is correct.
           Writing the count as `b-a+2` with `<` makes the intention clearer.
        4. The algorithm is O(n + m) time and O(1) auxiliary space.

    IMPORTANT:
        The problem constraints guarantee a >= 1 and b < list1.length - 1,
        so beforeA and afterB both exist. list2 is also non-empty.
        Do not delete the removed nodes unless the problem explicitly requires
        manual memory reclamation; LeetCode expects the returned chain to be
        correctly rewired.
*/
