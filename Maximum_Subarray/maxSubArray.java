import java.util.Arrays;

class Solution {
    public int maxSubArray(int[] nums) {
        int[] f = new int[nums.length];
        f[0] = nums[0];
        for (int i = 1; i < nums.length; i++) {
            f[i] = Math.max(nums[i] + f[i - 1], nums[i]);
        }
        return Arrays.stream(f).summaryStatistics().getMax();
    }
}
