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