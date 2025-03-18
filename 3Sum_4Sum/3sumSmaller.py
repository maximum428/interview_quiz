def three_sum_smaller(nums, target):
    if len(nums) < 3:
        return 0

    nums.sort()
    count = 0

    for i in range(len(nums) - 2):
        second = i + 1
        third = len(nums) - 1

        while second < third:
            sum = nums[i] + nums[second] + nums[third]
            if sum < target:
                count += (third - second)
                second += 1
            else:
                third -= 1

    return count

nums = [-2, 0, 1, 3]
target = 2

print(three_sum_smaller(nums, target))
