# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution(object):
    def rob(self, root):
        result = self.robber(root)
        return max(result[0], result[1])
    
    def robber(self, root):
        if root is None: return [0, 0]
        ret = [0, 0]
        left = self.robber(root.left)
        right = self.robber(root.right)
        
        ret[0] = max(left[0], left[1]) + max(right[0], right[1]);
        ret[1] = left[0] + right[0] + root.val
        return ret
