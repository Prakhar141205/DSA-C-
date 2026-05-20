class Solution {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        int n = A.size();

        vector<int> ans(n);
        vector<int> freq(n + 1, 0);

        int common = 0;

        for (int i = 0; i < n; i++) {

            freq[A[i]]++;
            if (freq[A[i]] == 2)
                common++;

            freq[B[i]]++;
            if (freq[B[i]] == 2)
                common++;

            ans[i] = common;
        }

        return ans;
    }
};


class Solution {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        int n = A.size();

        vector<int> ans(n);
        vector<int> freq(n + 1, 0);

        int common = 0;

        for (int i = 0; i < n; i++) {

            freq[A[i]]++;
            if (freq[A[i]] == 2)
                common++;

            freq[B[i]]++;
            if (freq[B[i]] == 2)
                common++;

            ans[i] = common;
        }

        return ans;
    }
};


class Solution {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        vector<int> C;
        unordered_map<int,int> hash;
        int count=0,n=A.size();
        for(int i=0;i<n;i++){
            hash[A[i]]++;hash[B[i]]++;
            if(hash[A[i]]==2 && A[i]!=B[i]) count++;
            if(hash[B[i]]==2 && A[i]!=B[i]) count++;
            else if(hash[A[i]]==2 && A[i]==B[i]) count++;
            C.push_back(count);

        }
        return C;
    }
};


class Solution {
public:
    // Brute Force:
    // Time Complexity: O(n^3)
    // Space Complexity: O(1)
    vector<int> findThePrefixCommonArray(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> result;

        for(int i = 0; i < n; i++) {

            int count = 0;
            for(int j = 0; j <= i; j++) {
                int a = nums1[j];

                for(int k = 0; k <= i; k++) {
                    int b = nums2[k];

                    if(a == b) {
                        count++;
                        break;
                    }
                }
            }

            result.push_back(count);
        }

        return result;
    }
};

class Solution {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        std::unordered_set<int> A_;
        std::unordered_set<int> B_;
        std::vector<int> ans(A.size(), 0);

        for (int i = 0; i < A.size(); ++i) {
            A_.insert(A[i]);
            B_.insert(B[i]);

            if (i > 0) {
                ans[i] = ans[i - 1];
            }

            if (B_.contains(A[i])) {
                ++ans[i];
            }

            if (B[i] != A[i] && A_.contains(B[i])) {
                ++ans[i];
            }
        }

        return ans;
    }
};