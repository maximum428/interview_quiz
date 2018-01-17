class Solution {
    public int FindUnsortedSubarray(int[] nums) {
        int n = nums.length, begin = -1, end = -2, min = Integer.MAX_VALUE, max = Integer.MIN_VALUE;
        
        for (int i = 0; i < n; i++) {
            max = Math.max(max, nums[i]);
            min = Math.min(min, nums[n-1-i]);
            if (nums[i] < max) end = i;
            if (nums[n-1-i] > min) begin = n-1-i;
        }

        return end - begin + 1;
    }

    public static void main(String[] args) {
        int[] nums = {2, 6, 4, 8, 10, 9, 15};
        Solution solution = new Solution();
        System.out.println(solution.FindUnsortedSubarray(nums));
    }
}
