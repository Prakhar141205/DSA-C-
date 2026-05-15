class Solution {
public:
    int findMin(vector<int>& nums) {
        
        int low  = 0;
        int high = nums.size() - 1;
        int n = nums.size();
        int ans  = INT_MAX;

        while (low <= high) {

            int mid = low + (high - low) / 2;

            if (nums[low] <= nums[mid]) {

                ans = min(ans,nums[low]);
                low = mid + 1;
            } else {

                ans = min (ans,nums[mid]);
                high = mid - 1;
            }
        }

        return ans;
    }
};

class Solution {
public:
    int findMin(vector<int>& nums) {
        int i,a=nums[0];
        for(i=1;i<nums.size();i++){
            if(a<=nums[i]){
                continue;
            }
            else{a=nums[i];}
        }
        return a;
        
    }
};

const size_t BUFFER_SIZE = 0x6fafffff;
alignas(std::max_align_t) char buffer[BUFFER_SIZE];
size_t buffer_pos = 0;

void* operator new(size_t size) {
    constexpr std::size_t alignment = alignof(std::max_align_t);
    size_t padding = (alignment - (buffer_pos % alignment)) % alignment;
    size_t total_size = size + padding;
    char* aligned_ptr = &buffer[buffer_pos + padding];
    buffer_pos += total_size;
    return aligned_ptr;
}

void operator delete(void* ptr, unsigned long) {}
void operator delete(void* ptr) {}
class Solution {
public:
    int findMin(vector<int>& nums) {
        int low = 0;
        int high = nums.size()-1;

        int ans = 5001;
        while(low <= high) {
            int mid = low + (high - low) / 2;
            if(nums[mid] >= nums[low]) {
                ans = min(ans,nums[low]);
                low = mid + 1;
            } else {
                ans = min(ans,nums[mid]);
                high = mid - 1;
            }
        }

        return ans;
    }
};

class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0, h=nums.size()-1;

        while(l < h){
            if(nums[l] < nums[h] ) return nums[l];

            int mid = l+ (h-l)/2;

            if(nums[mid] > nums[h]){
                l = mid + 1;

            }else{
                h =  mid;
            }
        }
        return nums[l];
    }
};