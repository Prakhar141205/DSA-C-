# Generation log

## Batch 1 — LeetCode 881: Boats to Save People

- **Status:** Complete
- **Original:** `Greedy Algorithm/881. Boats to Save People.cpp`
- **Approaches:** 5 (exhaustive recursion, memoized bitmask DP, bottom-up
  bitmask DP, sort/two pointers, frequency array/two pointers)
- **Validation:** Passed C++17 compilation. A randomized differential
  harness compared the three bitmask/exhaustive implementations against
  the sorting and frequency implementations on small inputs. Published
  example and boundary cases were included.
- **Artifacts:** `Solutions/Greedy/881_Boats_to_Save_People/`

The frequency-array and sort-based greedy strategies are both suitable
under the original constraints. Exponential approaches are explicitly
marked educational and small-input-only.

## Batch 2 — LeetCode 1328: Break a Palindrome

- **Status:** Complete
- **Original:** `Greedy Algorithm/1328. Break a Palindrome.cpp`
- **Approaches:** 2 (exhaustive replacement search, first-half greedy)
- **Validation:** Passed C++17 compilation. The greedy result was compared
  with exhaustive search for 160 generated palindromes over a three-letter
  alphabet, including length-one and all-`a` inputs.
- **Artifacts:** `Solutions/Greedy/1328_Break_a_Palindrome/`

## Batch 3 — Greedy references

### LeetCode 1578: Minimum Time to Make Rope Colorful

- **Status:** Complete
- **Original:** `Greedy Algorithm/1578. Minimum Time to Make Rope Colorful.cpp`
- **Approaches:** 4 (exhaustive recursion, memoized last-color DP,
  bottom-up last-color DP, run sum-minus-maximum greedy)
- **Validation:** Strict C++17 compilation passed. Differential testing
  passed 1,500 randomized short strings/cost vectors. Review identified
  that the original adjacent-index-only two-state DP can retain duplicate
  colors after deletions; it is called out in the notes and not included.
- **Artifacts:** `Solutions/Greedy/1578_Minimum_Time_to_Make_Rope_Colorful/`

### LeetCode 948: Bag of Tokens

- **Status:** Complete
- **Original:** `Greedy Algorithm/948. Bag of Tokens.cpp`
- **Approaches:** 3 (exhaustive DFS, memoized resource-state search,
  sort/two-pointer greedy)
- **Validation:** Strict C++17 compilation passed. Differential testing
  passed 600 randomized cases against both exhaustive implementations and
  the published example.
- **Artifacts:** `Solutions/Greedy/948_Bag_of_Tokens/`

### LeetCode 991: Broken Calculator

- **Status:** Complete
- **Original:** `Greedy Algorithm/brokenCalcualtor.cpp`
- **Approaches:** 2 (bounded forward BFS, reverse greedy)
- **Validation:** Strict C++17 compilation passed. BFS and greedy agreed
  for all 62,500 positive `(startValue, target)` pairs from 1 through 250.
- **Artifacts:** `Solutions/Greedy/991_Broken_Calculator/`
