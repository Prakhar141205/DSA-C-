class Solution:
    def rotate(self, nums: list[int], k: int) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        n = len(nums)
        k = k % n
        def reverse(l ,r):
            while(l < r) :
                nums[l], nums[r] = nums[r], nums[l]

                l += 1
                r -= 1

        reverse(0, n-k-1)
        reverse(n-k, n-1)
        reverse(0, n-1)


"""Implementation 2"""

class Solution:
    def reverse(self, nums: list[int], l: int, r: int ) -> None:

        while(l < r) :
            nums[l], nums[r] = nums[r], nums[l]
            l += 1
            r -= 1
        
    def rotate(self, nums: list[int], k: int) -> None:

        n = len(nums)
        k = k%n 

        self.reverse(0, n-k-1)
        self.reverse(n-k, n-1)
        self.reverse(0, n-1)
    