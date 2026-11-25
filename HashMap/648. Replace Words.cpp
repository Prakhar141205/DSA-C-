
/*************************************************************************** C++ ******************************************************************************************/
//Approach (Using normal hashset and generating all substrings)
//T.C : o(n*l + m*l^2) , n = number of words in the dictionary, m be the number of words in the sentence, and l be the average length of each word.
//S.C : O(n*l)
class Solution {
public:

    string findRoot(string& word, unordered_set<string>& st) {

        //try all length substring starting from 0th index
        for(int l = 1; l <= word.length(); l++) {
            string root = word.substr(0, l);
            if(st.count(root)) {
                return root;
            }
        }

        return word;

    }

    string replaceWords(vector<string>& dictionary, string sentence) {
        unordered_set<string> st(dictionary.begin(), dictionary.end());

        stringstream ss(sentence);
        string word;
        string result;

        while(getline(ss, word, ' ')) {
            result += findRoot(word, st) + " ";
        }

        result.pop_back();
        return result;

    }
};

class Solution {
public:
    string replaceWords(vector<string>& dictionary, string s) {
        int n = s.length();

        // Store all dictionary roots in an unordered_set
        // for O(1) average lookup.
        unordered_set<string> st(begin(dictionary), end(dictionary));

        string ans = "";
        int i = 0;

        while(i < n) {

            string temp = "";

            // Build the current word character by character.
            while(i < n and s[i] != ' ') {
                temp += s[i];

                // If the current prefix is present in the dictionary,
                // we have found the shortest root for this word.
                if(st.find(temp) != st.end()) {
                    break;
                }

                i++;
            }

            // Append the shortest root (or the original word
            // if no root is found) to the answer.
            ans += (temp + " ");

            // Skip the remaining characters of the current word.
            // This is useful when a root was found before the word ended.
            while(i < n and s[i] != ' ') {
                i++;
            }

            // Move past the space to process the next word.
            i++;
        }

        // Remove the extra trailing space from the answer.
        int t = ans.length();

        return ans.substr(0, t-1);
    }
};

/*************************************************************************** JAVA ******************************************************************************************/
//Approach (Using normal hashset and generating all substrings)
//T.C : o(n*l + m*l^2) , n = number of words in the dictionary, m be the number of words in the sentence, and l be the average length of each word.
//S.C : O(n*l)
class Solution {
    private String findRoot(String word, Set<String> st) {
        // Try all length substring starting from 0th index
        for (int l = 1; l <= word.length(); l++) {
            String root = word.substring(0, l);
            if (st.contains(root)) {
                return root;
            }
        }
        return word;
    }

    public String replaceWords(List<String> dictionary, String sentence) {
        Set<String> st = new HashSet<>(dictionary);
        
        StringBuilder result = new StringBuilder();
        String[] words = sentence.split(" ");
        
        for (String word : words) {
            result.append(findRoot(word, st)).append(" ");
        }
        
        // Remove the trailing space
        return result.toString().trim();
    }
}