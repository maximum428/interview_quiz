class NumArray {
    private int[] _nums;
    private int[] _sum;
    
    public NumArray(int[] nums) {
        _nums = nums;
        
        _sum = new int[nums.length + 1];
        for (int i = 0; i < nums.length; i++) {
            _sum[i + 1] = _sum[i] + nums[i];
        }
    }
    
    public int sumRange1(int i, int j) {
        int sum = 0;
        for (int k = i; k <= j; k++) {
            sum += _nums[k];
        }
        return sum;
    }
    
    public int sumRange2(int i, int j) {
        return _sum[j + 1] - _sum[i];
    }
    
    public static void main(String[] args) {
        int[] nums = { -2, 0, 3, -5, 2, -1 };
        NumArray obj = new NumArray(nums);
        
        System.out.println(obj.sumRange2(0, 2));
    }
}
