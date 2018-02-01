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
    public int rob(TreeNode root) {
        int[] result = robber(root);
        return Math.max(result[0], result[1]);
    }
    private int[] robber(TreeNode root) {
        if (root == null) return new int[2];
        int[] result = new int[2];
        int[] left = robber(root.left);
        int[] right = robber(root.right);
        result[0] = Math.max(left[0], left[1]) + Math.max(right[0], right[1]);
        result[1] = root.val + left[0] + right[0];
        return result;
    }
}
