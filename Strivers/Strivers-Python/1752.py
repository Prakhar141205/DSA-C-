class Solution:
    def check(self, nums: list[int]) -> bool:
        peak = 0
        n = len(nums)
        for i in range(n):
            if(nums[i] > nums[(i+1)%n]):
                peak += 1 
        return peak <= 1 
