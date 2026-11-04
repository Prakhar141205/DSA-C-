/*
    LeetCode 234. Palindrome Linked List
    Language: C++17

    LeetCode provides ListNode. Do not redefine it when submitting.

    Each approach is a separate class. Rename the chosen class to Solution.

    Problem:
        Return true if the linked-list values read forward and backward
        are identical.

    Recommended:
        Solution_ReverseSecondHalf — O(n) time and O(1) auxiliary space.
*/

#include <vector>
#include <stack>
using namespace std;

// -----------------------------------------------------------------------------
// Approach 1: Copy values into a vector, then compare from both ends
// Technique: Vector + two pointers
//
// Time:  O(n)
// Space: O(n)
//
// This is the simplest approach to understand. It does not modify the list.
// -----------------------------------------------------------------------------
class Solution_VectorTwoPointers {
public:
    bool isPalindrome(ListNode* head) {
        vector<int> values;

        for (ListNode* current = head; current != nullptr; current = current->next)
            values.push_back(current->val);

        int left = 0;
        int right = static_cast<int>(values.size()) - 1;

        while (left < right) {
            if (values[left] != values[right])
                return false;
            ++left;
            --right;
        }

        return true;
    }
};

// -----------------------------------------------------------------------------
// Approach 2: Stack the first half, then compare with the second half
// Technique: Stack + slow/fast pointers
//
// Time:  O(n)
// Space: O(n)
//
// Push the first half's values onto a stack. For an odd-sized list, skip the
// middle node. Then pop and compare against the second half.
// -----------------------------------------------------------------------------
class Solution_Stack {
public:
    bool isPalindrome(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return true;

        stack<int> firstHalf;
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            firstHalf.push(slow->val);
            slow = slow->next;
            fast = fast->next->next;
        }

        // Odd number of nodes: slow points to the middle node.
        if (fast != nullptr)
            slow = slow->next;

        while (slow != nullptr) {
            if (firstHalf.top() != slow->val)
                return false;

            firstHalf.pop();
            slow = slow->next;
        }

        return true;
    }
};

// -----------------------------------------------------------------------------
// Approach 3: Reverse the second half in place, compare, then restore
// Technique: Slow/fast pointers + in-place linked-list reversal
//
// Time:  O(n)
// Space: O(1)
//
// Steps:
//   1. Find the midpoint using slow and fast.
//   2. For odd length, skip the middle node.
//   3. Reverse the second half.
//   4. Compare the first half with the reversed second half.
//   5. Restore the second half before returning.
//
// Restoring the list is good practice because the function only needs to
// answer a question; it should not leave the caller's list modified.
// -----------------------------------------------------------------------------
class Solution_ReverseSecondHalf {
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
    bool isPalindrome(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return true;

        ListNode* slow = head;
        ListNode* fast = head;

        // When the loop ends:
        // - even length: slow is the first node of the second half
        // - odd length:  slow is the middle node
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // For odd length, do not compare the middle element with anything.
        if (fast != nullptr)
            slow = slow->next;

        ListNode* secondHalfReversed = reverseList(slow);

        ListNode* first = head;
        ListNode* second = secondHalfReversed;
        bool palindrome = true;

        while (second != nullptr) {
            if (first->val != second->val) {
                palindrome = false;
                break;
            }

            first = first->next;
            second = second->next;
        }

        // Restore the original list structure.
        reverseList(secondHalfReversed);

        return palindrome;
    }
};

// -----------------------------------------------------------------------------
// Approach 4: Recursive front/back comparison
// Technique: Recursion + a moving left-side pointer
//
// Time:  O(n)
// Space: O(n) recursion stack
//
// The recursion reaches the end of the list. While unwinding, each node is
// compared with a pointer that advances from the head.
// -----------------------------------------------------------------------------
class Solution_Recursive {
private:
    bool compareFromEnd(ListNode* right, ListNode*& left) {
        if (right == nullptr)
            return true;

        if (!compareFromEnd(right->next, left))
            return false;

        if (left->val != right->val)
            return false;

        left = left->next;
        return true;
    }

public:
    bool isPalindrome(ListNode* head) {
        ListNode* left = head;
        return compareFromEnd(head, left);
    }
};

// -----------------------------------------------------------------------------
// Approach 5: Find midpoint, reverse second half, compare (without restoring)
//
// Time:  O(n)
// Space: O(1)
//
// This is the shorter in-place variant. It leaves the second half reversed.
// Use Approach 3 when preserving the original list is important.
// -----------------------------------------------------------------------------
class Solution_ReverseWithoutRestore {
private:
    ListNode* reverseList(ListNode* head) {
        ListNode* previous = nullptr;

        while (head != nullptr) {
            ListNode* nextNode = head->next;
            head->next = previous;
            previous = head;
            head = nextNode;
        }

        return previous;
    }

public:
    bool isPalindrome(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return true;

        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        if (fast != nullptr)
            slow = slow->next; // Skip middle for odd length.

        ListNode* second = reverseList(slow);
        ListNode* first = head;

        while (second != nullptr) {
            if (first->val != second->val)
                return false;

            first = first->next;
            second = second->next;
        }

        return true;
    }
};

/*
    DRY RUN — Approach 3: Reverse the second half

    Example A:
        Input: 1 -> 2 -> 2 -> 1

        Find midpoint:
            slow = node 2 (index 2)
            fast = nullptr
        Even length, so second half begins at slow.

        Reverse second half:
            Original second half: 2 -> 1
            Reversed:             1 -> 2

        Compare:
            First half:  1, 2
            Reversed:    1, 2
            Both pairs match -> true

        Restore second half:
            1 -> 2 -> 2 -> 1

    Example B:
        Input: 1 -> 2 -> 3 -> 2 -> 1

        Find midpoint:
            slow = 3 (middle)
            fast != nullptr
        Skip middle:
            second half begins at the second 2.

        Reverse second half:
            2 -> 1 becomes 1 -> 2

        Compare:
            First half:  1, 2
            Reversed:    1, 2
            Both pairs match -> true

    Example C:
        Input: 1 -> 2

        Find midpoint:
            slow = 2
            fast = nullptr
        Reverse second half: 2
        Compare 1 with 2 -> mismatch -> false

    COMPLEXITY SUMMARY:
        Vector + two pointers:       O(n) time, O(n) space
        Stack + slow/fast:           O(n) time, O(n) space
        Reverse + restore:           O(n) time, O(1) space
        Recursive comparison:        O(n) time, O(n) call stack
        Reverse without restore:     O(n) time, O(1) space

    WHY APPROACH 3 IS O(1) EXTRA SPACE:
        It only uses a fixed number of pointers (slow, fast, first, second,
        previous, current, nextNode). It does not allocate an array, stack,
        or recursive call stack.

    IMPORTANT IMPLEMENTATION DETAIL:
        The second-half comparison loop stops when the second pointer reaches
        nullptr. The first half can have one extra node for odd-length lists;
        that middle node is intentionally not compared.
*/
