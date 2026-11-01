# LeetCode 1578 — Minimum Time to Make Rope Colorful

- **Original:** [`Greedy Algorithm/1578. Minimum Time to Make Rope Colorful.cpp`](../../../Greedy%20Algorithm/1578.%20Minimum%20Time%20to%20Make%20Rope%20Colorful.cpp)
- **Approaches:** 4
- **Recommended:** [SolutionRunGreedy](./Minimum_Time_to_Make_Rope_Colorful.cpp)

## Problem and observation

Remove balloons, paying their individual removal times, until no two
adjacent balloons have the same color. A maximal run of one color is
independent of every other run. From a run of `k` equal colors, at most one
balloon may remain; since removal costs are nonnegative, retain a maximum
cost balloon. The run cost is `sum(costs) - max(costs)`.

## Approaches

### 1. Keep/remove exhaustive recursion

At each index either remove the balloon (pay its cost) or keep it only if
its color differs from the last kept color. This examines every valid
subsequence of retained balloons. It is correct by exhaustive enumeration.
For `"aa"` with costs `[3,7]`, the optimal branch removes the first balloon
and keeps the second, paying 3.

There are `O(2^n)` branches and `O(n)` recursion depth. This is only
educational for tiny inputs; the stack can overflow for long strings.

### 2. Memoized DP by last retained color

State `(i,last)` is the minimum removal cost from suffix `i` onward given
that `last` is the previously retained color; sentinel 26 represents none.
Transition: remove current and pay its cost, or retain it at no cost if
its color differs from `last`. Base case at `i == n` is zero.

The recurrence covers every legal choice as approach 1, while memoization
evaluates each of at most `27n` states once. Time `O(27n)`, memo `O(27n)`,
stack `O(n)`. This is conceptually useful but recursive depth and memory
make it inferior to the linear greedy for maximum input.

### 3. Bottom-up DP by last kept color

`dp[last]` is the minimum cost for the processed prefix when `last` is the
most recently retained color; 26 is the empty-prefix state. For each
balloon, either remove it and keep `last`, or retain it if its color differs
from `last`.

This state is sufficient because future validity depends on the color of
the last retained balloon, not merely the previous input position. For
`"aaa"` with costs `[100,1,100]`, remembering the actual last retained
color correctly prevents deleting the middle balloon and retaining two
adjacent `a` balloons. There are 27 states and each is processed once per
balloon: `O(27n)` time and `O(27)` space.

### 4. Run sum-minus-maximum greedy (recommended)

Scan each maximal equal-color run and add its cost sum minus its largest
cost. For `"abaac"` with `[1,2,3,4,5]`, only the `"aa"` run conflicts:
`3 + 4 - 4 = 3`; answer is 3.

Every feasible result keeps at most one balloon per run. Keeping the
maximum-cost one minimizes the sum removed; choices between runs are
independent. Therefore summing these local minima is globally optimal.
The scan visits every balloon once: `O(n)` time and `O(1)` auxiliary space.
It does not mutate the costs.

## Original submission analysis

The original contains eight implementations: exhaustive recursion,
memoized color DP, bottom-up color DP, two-state DP, adjacent-pair greedy,
run scan, stack conflict resolution, and per-run sorting. The
adjacent-pair method carries the larger cost forward and adds the smaller
one; it is equivalent to run sum-minus-maximum. The run scan is the
recommended implementation. The stack stores one representative per run;
sorting each run adds work without changing which maximum is retained.

The original in-place adjacent-pair implementation mutates `neededTime`;
the generated run scan does not. Its small fixed alphabet makes color-state
DP possible, but does not make DP competitive with run scanning.

## Comparison

| Approach | Time | Auxiliary space | At constraints? |
|---|---:|---:|---|
| Exhaustive recursion | `O(2^n)` | `O(n)` stack | No |
| Memoized `(index,color)` DP | `O(27n)` | `O(27n) + O(n)` stack | Possible but not recommended |
| Bottom-up last-color DP | `O(27n)` | `O(27)` | Yes, but unnecessary |
| Run sum-minus-maximum | `O(n)` | `O(1)` | Yes; simplest |

Use `long long` for accumulated costs if constraints or input types are
extended. Important edge cases are empty input, one balloon, all-distinct
colors, one long run, and tied maximum costs.

**Interview follow-ups:** Explain why runs are independent; prove why the
maximum-cost balloon should remain; implement the adjacent-pair update;
compare DP and greedy; explain how a run summary can be maintained as
`sum` and `maximum`.

## Validation status

Compiled as C++17 and differentially compared across the four correct
approaches for short color strings and nonnegative costs. The original file
also contains a two-state recurrence based only on adjacent input colors;
that recurrence is not included because it can be incorrect when deletion
exposes an earlier same-colored balloon. Original implementation remains
unchanged.
