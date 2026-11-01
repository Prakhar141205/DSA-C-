# LeetCode 881 — Boats to Save People

- **Original:** [`Greedy Algorithm/881. Boats to Save People.cpp`](../../../Greedy%20Algorithm/881.%20Boats%20to%20Save%20People.cpp)
- **Original submissions:** 1
- **Topic:** Greedy, sorting, two pointers
- **Reference implementation:** [Boats_to_Save_People.cpp](./Boats_to_Save_People.cpp)
- **Approaches in this reference:** 5

## Problem understanding

Each boat can carry one or two people and has a maximum total weight `limit`.
Find the minimum number of boats that can carry everyone. Each person's
weight is at most the limit, so sending someone alone is always feasible.

The LeetCode constraints allow up to 50,000 people and bound weights by
30,000. The first three implementations are useful for understanding
optimization, but only the last two are appropriate at maximum constraints.

## Key observation and greedy derivation

Sort the weights. Let `light` be the lightest unassigned person and `heavy`
the heaviest unassigned person.

The heaviest person must use a boat in every feasible solution. If the
lightest and heaviest fit together, pairing them is safe: if the heaviest
were paired with someone else, that other partner is no lighter than the
lightest, so we can exchange partners without violating the limit. If they
do not fit, nobody remaining can fit with the heaviest, so that person must
go alone.

Thus every iteration accounts for exactly one boat, optionally assigning
both extremes.

## Approaches

### 1. Exhaustive recursive assignment

**Intuition.** Choose the first unassigned person. Try a boat alone, then
try pairing that person with every feasible unassigned partner. Take the
minimum.

**Algorithm.**
1. Find the first unused person.
2. Recurse after assigning that person alone.
3. For each feasible unused partner, recurse after assigning both.
4. Return the smallest boat count.

**Correctness.** Every valid arrangement either puts the selected person
alone or pairs them with exactly one other person. The recursion enumerates
both exhaustive cases and chooses their minimum.

**Dry run.** For `[1, 2, 2]`, `limit = 3`, choose weight 1. The singleton
branch can put both 2s together (2 boats total); pairing 1 with either 2
leaves the other 2 alone (also 2). The minimum is 2.

**Complexity.** The branching search has factorial-scale worst-case work
(an upper bound is `O(n!)`) and `O(n)` recursion/used-state space.

**Trade-offs.** Simple proof and no bit-width limit, but repeated equivalent
subproblems make it unusable beyond tiny inputs; recursion depth can also
be large.

### 2. Top-down bitmask DP

**Intuition.** The exhaustive search can revisit the same subset of assigned
people. Cache its answer using a bitmask.

**State and transition.** `dfs(mask)` is the minimum additional boats needed
when `mask` marks assigned people. Choose the first unset bit `i`:

`dfs(mask) = min(1 + dfs(mask | 1<<i), 1 + dfs(mask | 1<<i | 1<<j))`

The pair transition is allowed only for an unassigned `j` whose weight
combined with `i` is within the limit. The full mask is the zero-boat base
case.

**Correctness.** It caches the same exhaustive choices as approach 1, so it
preserves the recurrence while evaluating each subset once.

**Dry run.** For `[1, 2, 2]`, `limit = 3`, at the empty mask the first person
can go alone or pair with either 2. The pair states are equivalent in value;
the best completion uses two boats.

**Complexity.** There are `2^n` masks; each state scans up to `n` partners,
so `O(2^n * n)` time, `O(2^n)` memo space, and up to `O(n)` recursion stack.
Use only for small `n` (the implementation caps it at 20).

**Trade-offs.** Avoids repeated work and teaches subset DP, but remains
exponential. The cap returns `-1` outside its educational domain; it is not
a general LeetCode submission for large `n`.

### 3. Bottom-up bitmask DP

**Intuition.** Evaluate the same subset state graph iteratively.

**Algorithm.**
1. Set `dp[0] = 0` and all other states to infinity.
2. For every reachable mask, find its first unassigned person.
3. Relax a state assigning that person alone.
4. Relax one state for each feasible unassigned partner.
5. Return the full-mask value.

**Correctness.** Each transition adds at least one set bit, so masks are
visited in a topological order by increasing numeric value. Every assignment
is represented by a sequence of these legal transitions, and relaxation
keeps the minimum boat count for every subset.

**Dry run.** For three people, `dp[000]=0`. Assigning the first person alone
reaches `001` with cost 1; pairing them with either feasible partner reaches
a two-person mask with cost 1. Completing the remaining person gives the
full-mask cost 2.

**Complexity.** `O(2^n * n)` time and `O(2^n)` auxiliary space. This is still
only for small `n`.

**Trade-offs.** No recursion stack and an explicit state graph, but no
asymptotic improvement over memoization.

### 4. Sort + two-pointer greedy (recommended general solution)

**Algorithm.**
1. Sort weights increasingly.
2. Set `light = 0`, `heavy = n - 1`.
3. If two distinct remaining people fit, advance `light`.
4. Decrement `heavy` and increment the boat count.
5. Stop once the pointers cross.

**Correctness proof (exchange argument).** Consider an optimal assignment
for the remaining people. The heaviest person `H` must be on some boat. If
`H` shares with a person `X` and the lightest person `L` is unassigned,
then `L <= X`; replacing `X` with `L` cannot increase the boat's weight.
Therefore an optimal assignment exists that pairs `H` with `L` whenever
they fit. If `L + H > limit`, no remaining person can pair with `H`, so
`H` is alone in every solution. Removing the selected boat leaves the same
problem on fewer people; induction proves the algorithm optimal.

**Dry run.** `[1, 2, 2, 3]`, `limit = 3`:

| Remaining extremes | Decision | Boats |
|---|---|---:|
| 1 and 3 | pair | 1 |
| 2 and 2 | pair | 2 |

Answer: 2.

**Complexity.** Sorting costs `O(n log n)`; the scan moves each pointer at
most `n` times, costing `O(n)`. Auxiliary space is `O(log n)` for the
implementation-dependent sort stack and `O(1)` scan state.

**Trade-offs.** Fast, simple, works with a broad weight range, but sorts and
therefore mutates `people`.

### 5. Frequency array + two pointers

**Intuition.** The constraints bound each weight to a small integer range.
Store counts by weight instead of comparison-sorting the input.

**Algorithm.** Build a frequency vector, repeatedly locate the lightest and
heaviest non-empty weight buckets, place the heaviest on a boat, and also
remove the lightest if their sum fits.

**Correctness.** The frequency buckets represent the same sorted multiset
as the two-pointer method. The greedy proof for approach 4 applies
unchanged; equal-weight people are interchangeable.

**Dry run.** For `[1, 2, 2, 3]`, `limit = 3`, counts at weights 1, 2, 3 are
1, 2, 1. Pair 3 with 1; then pair the two remaining 2s. The answer is 2.

**Complexity.** Building counts costs `O(n)`. The heavy pointer decreases
through at most `limit` buckets; the light pointer advances through at most
`limit` buckets overall. Total `O(n + limit)` time and `O(limit)` auxiliary
space.

**Trade-offs.** Faster than comparison sorting when the domain is small,
but depends on positive bounded integer weights and allocates by `limit`.
For a huge or unbounded weight domain, use approach 4.

## Original submission analysis

The original is this same comprehensive variation file; it contains the
five algorithm families above plus alternate container/data-structure
expressions. Its recommended two-pointer method is optimal for the general
constraints. The frequency-array version is an additional constraint-aware
choice.

The original's bitmask methods are educational only and correctly guard the
small-`n` domain. Its sort/two-pointer condition checks `i < j`, which
prevents pairing a person with themself. The frequency implementation
consumes the heaviest first and then checks whether the lightest remaining
weight fits.

The sorting solution modifies the input vector; the frequency solution
does not. Intermediate pair sums are widened to `long long` in this
reference to avoid overflow if adapted to larger integer weights.

## Comparison

| # | Approach | Time | Auxiliary space | Fits original maximum constraints? |
|---:|---|---|---|---|
| 1 | Exhaustive recursion | Factorial-scale upper bound | `O(n)` | No |
| 2 | Top-down bitmask DP | `O(2^n * n)` | `O(2^n) + O(n)` stack | No |
| 3 | Bottom-up bitmask DP | `O(2^n * n)` | `O(2^n)` | No |
| 4 | Sort + two pointers | `O(n log n)` | `O(log n)` sort stack | Yes |
| 5 | Frequency array + pointers | `O(n + limit)` | `O(limit)` | Yes, uses weight bound |

## Interview review

**Why pair extremes rather than greedily pairing arbitrary people?** The
heaviest remaining person is forced to use a boat now. The lightest is the
only candidate that can maximize the chance of sharing that boat.

**What if the lightest and heaviest do not fit?** Since all other remaining
people weigh at least as much as the lightest, the heaviest must travel
alone.

**Does the algorithm require sorting in place?** No. A copy can be sorted
to preserve input, at the cost of `O(n)` extra space.

**Can counting sort help?** Yes, when weights are bounded by a small limit;
the frequency-array implementation avoids comparison sorting.

**Common mistakes.**
- Pairing when `light == heavy`, which would count one person twice.
- Pairing a heavy person with a non-lightest person while a lighter one is
  still unassigned.
- Forgetting that the algorithm counts a boat even when the heaviest person
  goes alone.
- Applying bitmask DP to the full input constraints.

**Edge cases.** Empty input returns 0; one person needs one boat; all
weights at the limit travel alone; a pair whose sum equals the limit fits;
duplicates are handled naturally.

**Follow-ups and patterns.** Ask for the minimum number of bins if boats
can hold more than two people (the problem becomes substantially harder);
ask how to preserve the input; compare comparison sorting against counting
sort; explain the exchange argument for the two-pointer greedy.

## Validation status

All five classes were compiled together with C++17. The three exact
approaches were compared on randomized small valid inputs; edge cases and
the published example were included. See `GENERATION_LOG.md` for the
recorded command and result.
