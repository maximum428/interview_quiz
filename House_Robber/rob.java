class Solution {
    public int rob(int[] nums) {
        int rob = 0;
        int no_rob = 0;
        for (int num : nums) {
            int tmp = no_rob + num;
            no_rob = Math.max(no_rob, rob);
            rob = tmp;
        }
        return Math.max(rob, no_rob);
    }
}
