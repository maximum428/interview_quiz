class Solution(object):
    def rob(self, nums):
        if len(nums) == 0:
            return 0
        if len(nums) == 1:
            return nums[0]
        
        rob_robf = nums[0]
        rob_nrobf = 0
        nrob_robf = 0
        nrob_nrobf = 0
        
        for num in nums[1:]:
            tmp = rob_nrobf + num
            rob_nrobf = max(rob_robf, rob_nrobf)
            rob_robf = tmp
            
            tmp = nrob_nrobf + num
            nrob_nrobf = max(nrob_robf, nrob_nrobf)
            nrob_robf = tmp
        
        return max(rob_nrobf, nrob_robf)
