### Key Learnings from This Question (C++ STL)

1. **`std::sort()` requirements:** Works with random-access iterators, such as those of `vector` and `array`, but not `map` or `set` iterators.

2. **Map ordering:** A `map` automatically sorts elements by **keys**, not values.

3. **Sorting by values:** To sort map entries by values, copy them into a `vector` and apply a custom comparator.

4. **Custom comparator:** Use a lambda function to define sorting criteria.
   ```cpp
   [](const auto& a, const auto& b) {
       return a.second > b.second;
   }
   ```
   This sorts in descending order of values.

5. **Map iterators:** `map` provides bidirectional iterators, whereas `vector` provides random-access iterators.

6. **Container choice:** Choose a container based on the operations you need. If you frequently need to sort elements by different criteria, a `vector` of pairs can be more convenient than a `map`.

7. **Time complexity:**
   - Copying `N` map entries into a vector: **O(N)**.
   - Sorting the vector: **O(N log N)**.

8. **Tie-breaking:** You can sort by value first and then by key when values are equal.
   ```cpp
   sort(v.begin(), v.end(), [](const auto& a, const auto& b) {
       if (a.second != b.second)
           return a.second > b.second;
       return a.first < b.first;
   });
   ```

**Remember:** `map` maintains key-based ordering; `sort()` rearranges random-access sequences. To sort map entries by values, use a vector and a custom comparator.