class Solution(object):
    def dominantIndex(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums) == 0: return -1
        
        maxOne = maxTwo = 0
        index = -1
        
        for i, n in enumerate(nums):
            if maxOne < n:
                maxTwo = maxOne
                maxOne = n
                index = i
            elif maxTwo < n:
                maxTwo = n
                
        if maxOne < maxTwo*2:
            index = -1
            
        return index
