def two_sum(nums, target):
    map = {}

    for i, num in enumerate(nums):
        complement = target - num
        if complement in map:
            return [map[complement], i]
        map[num] = i
    return []

def main():
    nums = [2, 7, 11, 15]
    target = 9

    res = two_sum(nums, target)

    if res:
        print(f"Indices: {res[0]}, {res[1]}")
    else:
        print("No solution found.")

if __name__ == "__main__":
    main()
