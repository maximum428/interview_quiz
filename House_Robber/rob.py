class Solution(object):
    def rob(self, nums):
        rob = no_rob = 0
        for num in nums:
            tmp = no_rob + num
            no_rob = max(rob, no_rob)
            rob = tmp
        return max(rob, no_rob)
