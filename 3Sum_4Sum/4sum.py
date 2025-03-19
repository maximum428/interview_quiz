def backtrack(nums, res, vec, target, value, start):
    if len(vec) == 4 and value == target:
        res.append(vec[:])
        return

    for i in range(start, len(nums)):
        if i > start and nums[i] == nums[i - 1]:
            continue
        vec.append(nums[i])
        backtrack(nums, res, vec, target, value + nums[i], i + 1)
        vec.pop()

def four_sum2(nums, target):
    res = []
    nums.sort()
    backtrack(nums, res, [], target, 0, 0)
    return res

def four_sum1(nums, target):
    res = []
    if len(nums) < 4:
        return res

    nums.sort()

    for i in range(len(nums) - 3):
        if i > 0 and nums[i] == nums[i - 1]:
            continue
        for j in range(i + 1, len(nums) - 2):
            if j > i + 1 and nums[j] == nums[j - 1]:
                continue
            third, four = j + 1, len(nums) - 1
            while third < four:
                sum_val = nums[i] + nums[j] + nums[third] + nums[four]
                if sum_val < target:
                    third += 1
                elif sum_val > target:
                    four -= 1
                else:
                    res.append([nums[i], nums[j], nums[third], nums[four]])
                    while third < four and nums[third] == nums[third + 1]:
                        third += 1
                    while third < four and nums[four] == nums[four - 1]:
                        four -= 1
    return res

def print_result(vecs):
    for vec in vecs:
        print(f"[{' '.join(map(str, vec))}]")

def main():
    nums = [1, 0, -1, 0, -2, 2]
    target = 0

    res1 = four_sum1(nums, target)
    #print_result(res1)

    #res2 = four_sum2(nums, target)
    #print_result(res2)

if __name__ == "__main__":
    main()
