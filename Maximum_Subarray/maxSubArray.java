import java.util.Arrays;

class Solution {
    public int maxSubArray1(int[] nums) {
        int[] f = new int[nums.length];
        f[0] = nums[0];
        for (int i = 1; i < nums.length; i++) {
            f[i] = Math.max(nums[i] + f[i - 1], nums[i]);
        }
        return Arrays.stream(f).summaryStatistics().getMax();
    }
    
    public int maxSubArray2(int[] nums) {
        //int[] f = new int[nums.length];
        //f[0] = nums[0];
        int max = nums[0];
        int sum = nums[0];
        for (int i = 1; i < nums.length; i++) {
            sum = Math.max(nums[i] + sum, nums[i]);
            max = Math.max(sum, max);
        }
        return max;
    }
}
