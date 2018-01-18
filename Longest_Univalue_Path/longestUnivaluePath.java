/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
class Solution {
    private int res = 0;
    public int longestUnivaluePath(TreeNode root) {
        travel(root);
        return res;
    }
    
    private int travel(TreeNode root) {
        if (root == null)
            return 0;
        int leftcount = travel(root.left);
        int rightcount = travel(root.right);
        int left = 0, right = 0;
        if (root.left != null && root.left.val == root.val) {
            left = leftcount + 1;
        }
        if (root.right != null && root.right.val == root.val) {
            right = rightcount + 1;
        }
        res = Math.max(res, left + right);
        return Math.max(left, right);
    }
}
