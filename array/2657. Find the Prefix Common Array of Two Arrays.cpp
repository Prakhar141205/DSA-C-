
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

// using bitmask arrays as a track record

class Solution {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        int n = A.size();
        vector<int> ans;
        vector<bool> maskA(n+1, false);
        vector<bool> maskB(n+1, false);

        for(int i=0; i<n; i++){
            maskA[A[i]]=true;
            maskB[B[i]]=true;

            int cmn=0;

            for(int j=1; j<=n; j++){
                if(maskA[j] && maskB[j]){
                    cmn++;
                }
            }

            ans.push_back(cmn);
        }

        return ans;
    }
};

// using the same approach but  noticing that the previous indes answer is always less than current => current >= previous index
// hence maintain a global common cnter 

class Solution { // O(N)
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        int n = A.size();
        vector<int> ans;
        vector<bool> maskA(n+1, false);
        vector<bool> maskB(n+1, false);

        int commoncnt = 0;
        for(int i=0; i<n; i++){
            int valA = A[i];
            int valB = B[i];

            maskA[valA]=true;
            if(maskB[valA]){
                commoncnt++;
            }

            maskB[valB]=true;

            if(maskA[valB] && valA != valB) {
                commoncnt++;
            }

            ans.push_back(commoncnt);
        }

        return ans;
    }
};

// using bitmask 
// long contain 64 bits => 000000......00000
// jo number present honge us place ki bit ki value 1 kr denge

#include <iostream>
#include <vector>
#include <string>
#include <bit>

class Solution {

    public:
    std::vector<int> findThePrefixCommonArray(std::vector<int>& A, std::vector<int>& B) {
        int n = A.size();
        std::vector<int> ans;
        unsigned long long maskA = 0;
        unsigned long long maskB = 0;

        int commoncnt = 0;
        for(int i=0; i<n; i++){
            maskA |= (1L << A[i]);

            maskB |= (1L << B[i]);

            ans.push_back(std::popcount(maskA & maskB));
        }

        return ans;
    }
};
int main(){

    std::vector<int> a = {1, 2, 3, 4};
    std::vector<int> b = {2, 1, 4, 3};

    Solution sol;
    std::vector<int> ans = sol.findThePrefixCommonArray(a, b);

    for(int x : ans){
        std::cout << x << " ";
    }

    return 0;
}