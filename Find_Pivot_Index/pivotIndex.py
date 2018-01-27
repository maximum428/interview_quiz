class Solution(object):
    def pivotIndex(self, nums):
        sub_sum = 0
        total = sum(nums)
        
        for index, x in enumerate(nums):
            if sub_sum == total - x - sub_sum:
                return index;
            sub_sum += x
        return -1
