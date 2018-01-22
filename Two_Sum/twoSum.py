class Solution(object):
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        if len(nums) <= 1:
            return False
        dict = {}
        for i in range(len(nums)):
            if nums[i] in dict:
                return [dict[nums[i]], i]
            else:
                dict[target - nums[i]] = i

if __name__ == "__main__":
    solution = Solution()
    nums = [ 2, 3, 4 ]
    for element in solution.twoSum(nums, 6):
        print element,
