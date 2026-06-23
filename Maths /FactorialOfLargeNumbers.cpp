// Factorial of large numbers

class Solution {
public:
    void multiply(vector<int>& arr, int multiplier, int& size){

        int carry = 0;

        for(int i=0; i<size; i++){
            int res = multiplier % 10;

            res = res + carry;
            arr[i] = res % 10;
            carry = res / 10;
     
        }

        while(carry > 0){
            arr[size++] = carry%10;

            carry /= 10;
        }
    }
    vector<int> largeNumberFactorial(int N){
        vector<int> arr(1e5, 0);

        arr[0] = 1;

        int size = 1;

        for(int multiplier = 2; multiplier <= N; multiplier++){
            multiply(arr, multiplier, size);
        }

        vector<int> result;

        for(int i = size-1; i>=0; i--){
            result.push_back(arr[i])
        }
        return result;
    }
};

int main(){


    Solution s;

    s.largeNumberFactorial(1000);
}