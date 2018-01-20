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
    public int getMinimumDifference(TreeNode root) {
        prev = null;
        min_diff = Integer.MAX_VALUE;
        inorder(root);
        return min_diff;
    }
    
    private void inorder(TreeNode root) {
        if (root == null) return;
        inorder(root.left);
        if (prev != null) min_diff = Math.min(min_diff, root.val - prev);
        prev = root.val;
        inorder(root.right);
    }
    
    private Integer prev;
    private int min_diff;
}
