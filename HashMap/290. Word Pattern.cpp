#include <bits/stdc++.h>
using namespace std;

/*
    LeetCode 290 - Word Pattern

    A valid match is a bijection:
      1. Every pattern character maps to exactly one word.
      2. Every word maps to exactly one pattern character.
      3. No two different characters share a word.
      4. The number of words must equal pattern.length().

    All classes are independent. Rename the chosen class to Solution
    before submitting to LeetCode.
*/


// -----------------------------------------------------------------------------
// Helper: split s into words. Constraints guarantee single spaces and no
// leading/trailing spaces.
// -----------------------------------------------------------------------------
static vector<string> splitWords(const string& s) {
    vector<string> words;
    stringstream ss(s);
    string word;

    while (ss >> word) {
        words.push_back(word);
    }
    return words;
}


// -----------------------------------------------------------------------------
// Approach 1: Brute force pairwise consistency check
// Time: O(n^2 * L) worst case; Space: O(n * L)
// n = pattern length, L = maximum word length.
// For every pair of positions, equal characters must correspond to equal
// words, and different characters must correspond to different words.
// -----------------------------------------------------------------------------
class SolutionBruteForce {
public:
    bool wordPattern(string pattern, string s) {
        vector<string> words = splitWords(s);
        int n = (int)pattern.size();

        if ((int)words.size() != n) return false;

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                bool sameCharacter = (pattern[i] == pattern[j]);
                bool sameWord = (words[i] == words[j]);

                if (sameCharacter != sameWord) {
                    return false;
                }
            }
        }

        return true;
    }
};


// -----------------------------------------------------------------------------
// Approach 2: Two direct-mapping arrays
// Time: O(n + |s|); Space: O(1) auxiliary, excluding parsed words.
// Since pattern contains only 'a'..'z', use a 26-element array for char->word.
// A reverse map is still needed to enforce word->char uniqueness.
// -----------------------------------------------------------------------------
class SolutionTwoMaps {
public:
    bool wordPattern(string pattern, string s) {
        vector<string> words = splitWords(s);
        if (words.size() != pattern.size()) return false;

        vector<string> charToWord(26);
        unordered_map<string, char> wordToChar;

        for (int i = 0; i < (int)pattern.size(); ++i) {
            int id = pattern[i] - 'a';
            const string& word = words[i];

            if (charToWord[id].empty() && !wordToChar.count(word)) {
                charToWord[id] = word;
                wordToChar[word] = pattern[i];
            } else {
                if (charToWord[id] != word) return false;
                if (wordToChar[word] != pattern[i]) return false;
            }
        }

        return true;
    }
};


// -----------------------------------------------------------------------------
// Approach 3: Two unordered maps
// Time: Average O(n + |s|); Space: O(k + w), mapping state.
// General-purpose bijection check using both directions.
// -----------------------------------------------------------------------------
class SolutionHashMaps {
public:
    bool wordPattern(string pattern, string s) {
        vector<string> words = splitWords(s);
        if (words.size() != pattern.size()) return false;

        unordered_map<char, string> charToWord;
        unordered_map<string, char> wordToChar;

        for (int i = 0; i < (int)pattern.size(); ++i) {
            char c = pattern[i];
            const string& word = words[i];

            auto it1 = charToWord.find(c);
            auto it2 = wordToChar.find(word);

            if (it1 != charToWord.end() && it1->second != word) {
                return false;
            }

            if (it2 != wordToChar.end() && it2->second != c) {
                return false;
            }

            charToWord[c] = word;
            wordToChar[word] = c;
        }

        return true;
    }
};


// -----------------------------------------------------------------------------
// Approach 4: One map + set of already-used words
// Time: Average O(n + |s|); Space: O(k + w).
// The map enforces character->word consistency; the set prevents two
// characters from claiming the same word.
// -----------------------------------------------------------------------------
class SolutionMapAndSet {
public:
    bool wordPattern(string pattern, string s) {
        vector<string> words = splitWords(s);
        if (words.size() != pattern.size()) return false;

        unordered_map<char, string> charToWord;
        unordered_set<string> usedWords;

        for (int i = 0; i < (int)pattern.size(); ++i) {
            char c = pattern[i];
            const string& word = words[i];

            auto it = charToWord.find(c);

            if (it != charToWord.end()) {
                if (it->second != word) return false;
            } else {
                if (usedWords.count(word)) return false;

                charToWord[c] = word;
                usedWords.insert(word);
            }
        }

        return true;
    }
};


// -----------------------------------------------------------------------------
// Approach 5: Canonical first-occurrence pattern (last-seen indices)
// Time: Average O(n + |s|); Space: O(k + w).
// Two values are equivalent exactly when their previous-occurrence positions
// match. Using maps with last-seen index checks both directions.
// -----------------------------------------------------------------------------
class SolutionLastSeenIndex {
public:
    bool wordPattern(string pattern, string s) {
        vector<string> words = splitWords(s);
        if (words.size() != pattern.size()) return false;

        unordered_map<char, int> lastChar;
        unordered_map<string, int> lastWord;

        for (int i = 0; i < (int)pattern.size(); ++i) {
            char c = pattern[i];
            const string& word = words[i];

            int charIndex = lastChar.count(c) ? lastChar[c] : -1;
            int wordIndex = lastWord.count(word) ? lastWord[word] : -1;

            if (charIndex != wordIndex) return false;

            lastChar[c] = i;
            lastWord[word] = i;
        }

        return true;
    }
};


// -----------------------------------------------------------------------------
// Approach 6: Single unordered map with tagged keys
// Time: Average O(n + |s|); Space: O(k + w).
// Store pattern characters and words in one map using distinct prefixes.
// The tags prevent a character key from colliding with a word key.
// -----------------------------------------------------------------------------
class SolutionSingleMapTaggedKeys {
public:
    bool wordPattern(string pattern, string s) {
        vector<string> words = splitWords(s);
        if (words.size() != pattern.size()) return false;

        unordered_map<string, int> firstSeen;

        for (int i = 0; i < (int)pattern.size(); ++i) {
            string charKey = "C:";
            charKey += pattern[i];

            string wordKey = "W:" + words[i];

            int charSeen = firstSeen.count(charKey) ? firstSeen[charKey] : -1;
            int wordSeen = firstSeen.count(wordKey) ? firstSeen[wordKey] : -1;

            if (charSeen != wordSeen) return false;

            firstSeen[charKey] = i;
            firstSeen[wordKey] = i;
        }

        return true;
    }
};


/*
    Example:
      pattern = "abba"
      s       = "dog cat cat dog"

      Position:  0     1     2     3
      Pattern:   a     b     b     a
      Word:      dog   cat   cat   dog

      a <-> dog
      b <-> cat

      Both directions are consistent, so return true.

    Why the submitted implementation is incorrect:
      - It checks only whether one pattern character maps to multiple words.
      - It does not ensure that two different pattern characters map to
        different words. For example:
            pattern = "ab"
            s = "dog dog"
        Your set-per-character approach would accept this, but the required
        mapping is not bijective.
      - It assumes the number of words matches the pattern length and can
        access pattern[i] out of bounds if there are too many words.
      - It prints debug output, which is unnecessary.

    Recommended:
      - Approach 3: standard, explicit two-way hash-map solution.
      - Approach 5: elegant last-seen-index technique.
*/
