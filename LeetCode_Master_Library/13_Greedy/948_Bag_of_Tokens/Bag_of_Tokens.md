# LeetCode 948 — Bag of Tokens

- **Original:** [`Greedy Algorithm/948. Bag of Tokens.cpp`](../../../Greedy%20Algorithm/948.%20Bag%20of%20Tokens.cpp)
- **Approaches:** 3
- **Recommended:** [SolutionGreedy](./Bag_of_Tokens.cpp)

## Rules and state

A token may be played once. Face-up spends its value in power for one score;
face-down spends one score to gain its value in power. Maximize the highest
score reached, not necessarily the final score.

## 1. Exhaustive DFS

Try every unplayed token in every legal orientation. Track current power,
score, and the maximum score seen. This enumerates all legal play
sequences, so the maximum encountered is correct.

For tokens `[100, 200]` and power 150, buying 100 gives score 1 and power
50, but the 200 token cannot be played face-up; selling it face-down is
illegal because no further score is available. The best score is 1.

The number of sequences is exponential with factorial ordering choices;
recursion uses `O(n)` stack. It is only useful as a tiny-input baseline.

## 2. Memoized state search

Cache by `(used-token mask, power, score)`. The mask alone is insufficient:
playing tokens in different orientations changes both power and score.
Each state tries every legal move, so memoization avoids revisiting identical
resource states while retaining exhaustive correctness.

The reachable state count is exponential in the worst case, with `O(n)`
transitions per state. It is for small inputs only; this implementation
returns `-1` above 20 tokens to prevent an unsafe bitmask shift and
unmanageable state space.

## 3. Sort + greedy two pointers

Sort token values. Keep `left` at the cheapest unused token and `right` at
the most expensive:

1. If the cheapest token is affordable, play it face-up. This obtains a
   score for the least power cost.
2. Otherwise, if at least one score exists and a distinct token remains,
   play the most expensive remaining token face-down. This obtains the
   greatest possible power for the score spent.
3. Otherwise stop.
4. Track `best` after every face-up play because a later face-down move
   decreases current score.

### Greedy reasoning

Among face-up choices, a more expensive token cannot yield more score and
leaves less power, so the cheapest affordable token is never worse.
When no remaining token can be bought, spending a score on the most
expensive token maximizes the power available for subsequent purchases.
An exchange can replace any cheaper sale with the largest remaining token,
leaving at least as much power and the same score. Repeating these choices
produces an optimal score.

**Dry run:** `[100, 200, 300, 400]`, power 200:

| Action | Power | Score | Best |
|---|---:|---:|---:|
| Buy 100 | 100 | 1 | 1 |
| Cannot buy 200; sell 400 | 500 | 0 | 1 |
| Buy 200 | 300 | 1 | 1 |
| Buy 300 | 0 | 2 | 2 |

The answer is 2. Sorting costs `O(n log n)` and the pointers move at most
`n` times. Extra space is `O(log n)` for the sort stack. Sorting mutates the
input.

## Original submission analysis

The original contains exhaustive DFS, memoization, BFS state exploration,
the standard sorted two-pointer greedy, deque and multiset versions, a
two-heap version, and a compact greedy version. The first three are
state-space baselines; BFS explores the same exponential transition graph
as DFS and is not a distinct asymptotic improvement. Deque/multiset/heap
implementations maintain the same smallest/largest greedy choices with
extra bookkeeping. The reference keeps exhaustive DFS, memoized state
search, and the optimal sorted greedy to represent the distinct algorithmic
ideas.

The source's heap implementation deserves caution: lazy deletion needs
correctly tracked active tokens and does not improve on sorting a static
array. The sorted greedy is closest to the recommended solution. Intermediate
power is widened to `long long` in the reference.

## Comparison and edge cases

| Approach | Time | Space | Suitable for n <= 1000? |
|---|---:|---:|---|
| Exhaustive DFS | Exponential | `O(n)` stack | No |
| Memoized state search | Exponential worst case | Exponential | No |
| Sort + greedy | `O(n log n)` | `O(log n)` sort stack | Yes |

Important cases: no tokens; power below the cheapest token and score zero;
all tokens affordable; selling only when score is positive; and tracking
maximum score separately from current score.

**Interview follow-ups:** Why buy the cheapest? Why sell the largest?
Why is `best` needed separately? Can the input be preserved by sorting a
copy? What state would exact search require?

## Validation status

Compiled as C++17 and differentially compared with both exhaustive
implementations on small token sets, including the published example,
empty input, insufficient power, and repeated token values.
