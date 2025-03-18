def three_sum_closest(nums, target):
    if len(nums) < 3:
        return 0

    nums.sort()
    closest = nums[0] + nums[1] + nums[2];

    for i in range(len(nums) - 2):
        second = i + 1
        third = len(nums) - 1

        while second < third:
            sum = nums[i] + nums[second] + nums[third]
            if sum == target:
                return sum
            if abs(target - sum) < abs(target - closest):
                closest = sum
            elif sum < target:
                second += 1
            else:
                third -= 1
    return closest

nums = [-1, 2, 1, -4]
target = 1
print(three_sum_closest(nums, target))
