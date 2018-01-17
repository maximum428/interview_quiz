class Solution(object):
    def findUnsortedSubarray(self, nums):
        is_same = [a == b for a, b in zip(nums, sorted(nums))]
        return 0 if all(is_same) else len(nums) - is_same.index(False) - is_same[::-1].index(False)
    
if __name__ == "__main__":
    solution = Solution()
    nums = [2, 6, 4, 8, 10, 9, 15]
    print solution.findUnsortedSubarray(nums);
