/*
LeetCode 138: Copy List with Random Pointer
All approaches from brute force to optimal.

LeetCode already provides the Node class:
class Node {
public:
    int val;
    Node* next;
    Node* random;
    Node(int _val) : val(_val), next(nullptr), random(nullptr) {}
};

This file uses Solution1, Solution2, ... so the approaches can coexist.
For submission, copy ONE class and rename it to Solution.
*/

#include <unordered_map>
#include <vector>
using namespace std;

/*
APPROACH 1: Brute force — for each random pointer, search for its target
Idea:
1. First pass: create a copy node for every original node, connect copied next pointers,
   and store the copied nodes in a vector in the same order.
2. For each original node's random pointer, linearly search the original list to find
   the target node's index.
3. Set the copied node's random pointer to the copied node at that index.

Time:  O(n^2) — each random pointer may require scanning the list.
Space: O(n) — copied nodes and vector.
*/
class Solution1 {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) return nullptr;

        vector<Node*> copies;
        Node* curr = head;
        Node* copyHead = new Node(curr->val);
        copies.push_back(copyHead);

        Node* copyTail = copyHead;
        curr = curr->next;

        while (curr != nullptr) {
            copyTail->next = new Node(curr->val);
            copyTail = copyTail->next;
            copies.push_back(copyTail);
            curr = curr->next;
        }

        Node* original = head;
        int i = 0;

        while (original != nullptr) {
            if (original->random != nullptr) {
                Node* scan = head;
                int j = 0;

                while (scan != original->random) {
                    scan = scan->next;
                    ++j;
                }

                copies[i]->random = copies[j];
            }

            original = original->next;
            ++i;
        }

        return copyHead;
    }
};

/*
APPROACH 2: Hash map — original node -> copied node (RECOMMENDED)
Idea:
1. First pass: create a copy for each original node and store map[original] = copy.
2. Second pass: connect each copied node's next and random pointers using the map.

Time:  O(n) average
Space: O(n) for the hash map, in addition to the output list.
*/
class Solution2 {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) return nullptr;

        unordered_map<Node*, Node*> mp;
        Node* curr = head;

        // Create one copied node for every original node.
        while (curr != nullptr) {
            mp[curr] = new Node(curr->val);
            curr = curr->next;
        }

        // Wire the copied nodes' next and random pointers.
        curr = head;
        while (curr != nullptr) {
            mp[curr]->next = (curr->next != nullptr) ? mp[curr->next] : nullptr;
            mp[curr]->random = (curr->random != nullptr) ? mp[curr->random] : nullptr;
            curr = curr->next;
        }

        return mp[head];
    }
};

/*
APPROACH 3: Interweaving / weaving nodes (OPTIMAL AUXILIARY SPACE)
Idea:
1. Insert each copy immediately after its original:
   A -> B -> C becomes A -> A' -> B -> B' -> C -> C'.
2. For every original node, if original->random points to R, then its copy's
   random pointer is R->next (the copy of R).
3. Separate the interwoven list into the original and copied lists.

Time:  O(n)
Auxiliary space: O(1) (the copied nodes are output, not auxiliary storage).
Important: This temporarily modifies the original list, then restores it.
*/
class Solution3 {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) return nullptr;

        Node* curr = head;

        // Step 1: Insert each copied node after its original node.
        while (curr != nullptr) {
            Node* copy = new Node(curr->val);
            copy->next = curr->next;
            curr->next = copy;
            curr = copy->next;
        }

        // Step 2: Set random pointers on copied nodes.
        curr = head;
        while (curr != nullptr) {
            Node* copy = curr->next;
            if (curr->random != nullptr) {
                copy->random = curr->random->next;
            }
            curr = copy->next;
        }

        // Step 3: Separate the original and copied lists.
        Node* copyHead = head->next;
        curr = head;

        while (curr != nullptr) {
            Node* copy = curr->next;
            curr->next = copy->next;

            if (copy->next != nullptr) {
                copy->next = copy->next->next;
            }

            curr = curr->next;
        }

        return copyHead;
    }
};

/*
COMPLEXITY SUMMARY (n = number of nodes)

Approach                                  Time       Auxiliary space
1. Linear search for each random target  O(n^2)     O(n)
2. Hash map (recommended)                O(n) avg   O(n)
3. Interweaving nodes                    O(n)       O(1)

Recommended for clarity/interviews: Approach 2 (hash map).
Recommended when O(1) auxiliary space is required: Approach 3 (interweaving).
All approaches create entirely new nodes; copied next/random pointers refer
only to copied nodes, never to original nodes.
*/
