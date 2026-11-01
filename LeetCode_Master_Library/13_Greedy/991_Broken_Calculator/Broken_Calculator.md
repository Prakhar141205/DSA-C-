# LeetCode 991 — Broken Calculator

- **Original:** [`Greedy Algorithm/brokenCalcualtor.cpp`](../../../Greedy%20Algorithm/brokenCalcualtor.cpp)
- **Approaches:** 2
- **Recommended:** [SolutionReverseGreedy](./Broken_Calculator.cpp)

## Problem

Starting from `startValue`, an operation either doubles the current value
or subtracts one. Find the minimum operations to reach `target`.

## 1. Forward BFS (educational)

Treat positive integers as graph vertices and the two operations as
unit-cost edges. Breadth-first search finds a shortest path because all
edges have equal cost. The implementation uses a finite upper bound `2 *
target` and refuses very large targets; it is intended only for small
inputs. Its time and space are `O(target)` under that bound.

**Dry run:** `startValue = 2`, `target = 3`: BFS sees `2 -> 4` and `2 -> 1`;
from 4 it can subtract to 3, giving 2 operations.

**Limitation:** BFS is a useful shortest-path baseline, not a practical
solution when target can reach `10^9`. Dijkstra is unnecessary because all
edges have equal cost. DFS/backtracking also explores the same graph with
less favorable behavior.

## 2. Reverse greedy

Work backward from `target`:

- If the current value is odd and above the start, increment it. This
  reverses a forward decrement and makes it even.
- If it is even and above the start, halve it. This reverses a forward
  doubling.
- Once it is no larger than `startValue`, reach the start by reverse
  increments; equivalently, the forward calculator performs
  `startValue - current` decrements before the remaining route.

### Correctness intuition

When reversing an odd value, division is not an integer predecessor of a
doubling, so incrementing is necessary. For an even value, halving undoes
one doubling immediately. Choosing increment instead would move farther
from the start and require at least as much subsequent work; replacing
that choice with halving cannot increase the number of operations.
When the reverse state drops below the start, the forward path's remaining
operations are forced decrements from `startValue` to that value.

**Dry run:** `startValue = 3`, `target = 10`:

| Reverse state | Action | Operations |
|---:|---|---:|
| 10 | halve | 1 |
| 5 | increment to 6 | 2 |
| 6 | halve | 3 |
| 3 | stop | 3 |

Answer: 3 (`3 -> 6 -> 5 -> 10` in forward order).

Each iteration either halves the value or increments an odd value once
before halving, so there are `O(log target)` iterations. Extra space is
`O(1)`. `long long` safely handles the odd-state increment.

## Original submission analysis

The original file contains forward BFS, forward Dijkstra, forward DFS,
bounded queue relaxation, reverse BFS, reverse recursive greedy, and
multiple equivalent reverse iterative variants. Forward BFS and Dijkstra
are shortest-path formulations; since every edge costs one, BFS is the
appropriate one. The reverse implementations use the optimal greedy
recurrence; naming or slightly changing the loop does not create a new
algorithm. This reference keeps one search baseline and one optimal
algorithm.

The original's reverse greedy is closest to the recommended implementation.
The bounded forward methods are educational and cannot handle maximum
constraints. This reference does not modify the source.

## Comparison

| Approach | Time | Auxiliary space | At original constraints? |
|---|---:|---:|---|
| Forward BFS | `O(target)` | `O(target)` | No |
| Reverse greedy | `O(log target)` | `O(1)` | Yes |

**Edge cases:** `startValue == target` gives 0; `startValue > target` uses
only decrements; target odd; repeated odd increment followed by halving.

**Common mistakes:** applying forward greedy without considering parity;
using Dijkstra instead of BFS on unit edges; overflowing `2*x` in a BFS;
forgetting to count the final gap when the reverse value falls below the
start.

**Follow-ups:** Prove the reverse exchange argument; derive a loop invariant;
compare BFS with greedy; estimate the number of iterations for `10^9`.

## Validation status

Compiled as C++17 and compared against BFS across all positive start/target
pairs up to 250, including equal, increasing, and decreasing cases.
