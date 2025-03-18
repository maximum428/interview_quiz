def backtrack(nums, res, vec, value, start):
    if len(vec) == 3 and value == 0:
        res.append(vec[:]);
        return

    for i in range(start, len(nums)):
        if i > start and nums[i] == nums[i-1]:
            continue
        vec.append(nums[i])
        backtrack(nums, res, vec, value+nums[i], i+1)
        vec.pop()

def three_sum1(nums):
    res = []
    vec = []
    nums.sort()
    backtrack(nums, res, vec, 0, 0)
    return res

def three_sum2(nums):
    res = []
    nums.sort()

    for i in range(len(nums)):
        first = -nums[i]
        second = i + 1
        third = len(nums) - 1

        while second < third:
            sum = nums[second] + nums[third]
            if first > sum:
                second += 1
            elif first < sum:
                third -= 1
            else:
                res.append([nums[i], nums[second], nums[third]])
                while second < third and nums[second] == nums[second+1]:
                    second += 1
                while second < third and nums[third] == nums[third-1]:
                    third -= 1
        while i + 1 < len(nums) and nums[i] == nums[i+1]:
            i += 1

    return res

def main():
    nums = [-1, 0, 1, 2, -1, -4]

    res1 = three_sum1(nums)
    for vec in res1:
        print(vec)

    res2 = three_sum2(nums)
    for vec in res2:
        print(vec)
    
if __name__ == "__main__":
    main()
