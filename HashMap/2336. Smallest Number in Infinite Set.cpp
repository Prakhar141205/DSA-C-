#include <bits/stdc++.h>
using namespace std;

/*
    LeetCode 2336 - Smallest Number in Infinite Set

    The set initially contains every positive integer.

    Key observation:
      - Keep `nextNumber` as the smallest positive integer that has never
        been popped from the original increasing sequence.
      - Any number added back must be smaller than `nextNumber`.
      - Store only these added-back numbers in a min-heap / ordered set.
      - Track membership to prevent duplicate addBack entries.

    Each class below is a complete, independent LeetCode design solution.
    Submit only ONE class, renamed to `SmallestInfiniteSet`.
*/


// -----------------------------------------------------------------------------
// Approach 1: Explicit bounded ordered set (similar to your solution)
// popSmallest: O(log B)
// addBack:     O(log B)
// Space:       O(B)
// B is an arbitrary fixed upper bound, not a true representation of infinity.
// For this problem, at most 1000 operations are made and num <= 1000, so
// 10000 is comfortably sufficient for the stated constraints.
// -----------------------------------------------------------------------------
class SmallestInfiniteSetBoundedSet {
private:
    set<int> available;

public:
    SmallestInfiniteSetBoundedSet() {
        for (int x = 1; x <= 10000; ++x) {
            available.insert(x);
        }
    }

    int popSmallest() {
        int answer = *available.begin();
        available.erase(available.begin());
        return answer;
    }

    void addBack(int num) {
        available.insert(num); // set ignores duplicates
    }
};


// -----------------------------------------------------------------------------
// Approach 2: Ordered set of added-back values + increasing pointer
// popSmallest: O(log k) when returning an added-back value; O(1) otherwise
// addBack:     O(log k)
// Space:       O(k), k = number of distinct pending added-back values
//
// `nextNumber` represents the untouched infinite suffix:
// [nextNumber, nextNumber+1, nextNumber+2, ...].
// Only values below nextNumber can be pending in `addedBack`.
// -----------------------------------------------------------------------------
class SmallestInfiniteSetOrderedSet {
private:
    int nextNumber;
    set<int> addedBack;

public:
    SmallestInfiniteSetOrderedSet() : nextNumber(1) {}

    int popSmallest() {
        if (!addedBack.empty()) {
            int smallestAdded = *addedBack.begin();

            if (smallestAdded < nextNumber) {
                addedBack.erase(addedBack.begin());
                return smallestAdded;
            }
        }

        return nextNumber++;
    }

    void addBack(int num) {
        // If num >= nextNumber, it is already in the untouched infinite suffix.
        if (num < nextNumber) {
            addedBack.insert(num);
        }
    }
};


// -----------------------------------------------------------------------------
// Approach 3: Min-heap + unordered_set + increasing pointer
// popSmallest: O(log k) if heap is used, O(1) otherwise
// addBack:     Average O(log k) due to heap insertion; O(1) hash membership
// Space:       O(k)
//
// The heap gives access to the smallest added-back value.
// The set prevents duplicate values from entering the heap.
// -----------------------------------------------------------------------------
class SmallestInfiniteSetMinHeap {
private:
    int nextNumber;
    priority_queue<int, vector<int>, greater<int>> minHeap;
    unordered_set<int> pending;

public:
    SmallestInfiniteSetMinHeap() : nextNumber(1) {}

    int popSmallest() {
        if (!minHeap.empty()) {
            int smallestAdded = minHeap.top();

            if (smallestAdded < nextNumber) {
                minHeap.pop();
                pending.erase(smallestAdded);
                return smallestAdded;
            }
        }

        return nextNumber++;
    }

    void addBack(int num) {
        if (num < nextNumber && pending.insert(num).second) {
            minHeap.push(num);
        }
    }
};


// -----------------------------------------------------------------------------
// Approach 4: Min-heap + boolean membership array + increasing pointer
// popSmallest: O(log k) if heap is used, O(1) otherwise
// addBack:     O(log k)
// Space:       O(B)
//
// Uses the problem's constraints (num <= 1000 and at most 1000 operations).
// A popped number cannot grow beyond 2000: at most 1000 popSmallest calls
// can advance nextNumber from 1 to 1001; addBack itself is restricted to 1000.
// The array is therefore sized with safe extra capacity.
// -----------------------------------------------------------------------------
class SmallestInfiniteSetHeapWithArray {
private:
    int nextNumber;
    priority_queue<int, vector<int>, greater<int>> minHeap;
    vector<bool> pending;

public:
    SmallestInfiniteSetHeapWithArray()
        : nextNumber(1), pending(2005, false) {}

    int popSmallest() {
        if (!minHeap.empty() && minHeap.top() < nextNumber) {
            int answer = minHeap.top();
            minHeap.pop();
            pending[answer] = false;
            return answer;
        }

        return nextNumber++;
    }

    void addBack(int num) {
        if (num < nextNumber && !pending[num]) {
            pending[num] = true;
            minHeap.push(num);
        }
    }
};


// -----------------------------------------------------------------------------
// Approach 5: Ordered set of returned numbers + pointer (without storing
// duplicates) — same core representation as Approach 2, with a compact
// alternative implementation.
// popSmallest: O(log k) for a returned number, otherwise O(1)
// addBack:     O(log k)
// Space:       O(k)
// -----------------------------------------------------------------------------
class SmallestInfiniteSetCompact {
private:
    int current = 1;
    set<int> returned;

public:
    SmallestInfiniteSetCompact() = default;

    int popSmallest() {
        if (!returned.empty() && *returned.begin() < current) {
            int answer = *returned.begin();
            returned.erase(returned.begin());
            return answer;
        }

        return current++;
    }

    void addBack(int num) {
        if (num < current) {
            returned.insert(num);
        }
    }
};


/*
    Example operation trace:
      Initially:
        nextNumber = 1
        addedBack = {}

      addBack(2):
        2 >= nextNumber, so 2 is already present. No change.

      popSmallest():
        return 1; nextNumber becomes 2.

      popSmallest():
        return 2; nextNumber becomes 3.

      popSmallest():
        return 3; nextNumber becomes 4.

      addBack(1):
        1 < nextNumber, so insert 1 into addedBack.

      popSmallest():
        return 1 from addedBack.

      popSmallest():
        return 4; nextNumber becomes 5.

      popSmallest():
        return 5; nextNumber becomes 6.


    Notes about your bounded-set implementation:
      - It is accepted because the constraints cap the number of operations
        and the input to addBack is at most 1000.
      - However, it materializes a finite range [1, 10000], not an infinite set.
      - A pointer-based implementation stores only the exceptional values
        that were popped and later added back, which is the scalable design.

    Recommended:
      - Approach 2: ordered set + pointer; concise and easy to reason about.
      - Approach 3: min-heap + hash set + pointer; demonstrates heap usage.
*/
