def find_prev_less(nums):
    size = len(nums)
    prev_less = [-1] * size
    stack = []

    for i in range(size):
        while stack and nums[stack[-1]] > nums[i]:
            stack.pop()
        prev_less[i] = stack[-1] if stack else -1
        stack.append(i)

    return prev_less

def find_next_less(nums):
    size = len(nums)
    next_less = [-1] * size
    stack = []

    for i in range(size):
        while stack and nums[stack[-1]] > nums[i]:
            x = stack.pop()
            next_less[x] = i
        stack.append(i)

    return next_less

def find_prev_large(nums):
    size = len(nums)
    prev_large = [-1] * size
    stack = []

    for i in range(size):
        while stack and nums[stack[-1]] < nums[i]:
            stack.pop()
        prev_large[i] = stack[-1] if stack else -1
        stack.append(i)

    return prev_large

def find_next_large(nums):
    size = len(nums)
    next_large = [-1] * size
    stack = []

    for i in range(size):
        while stack and nums[stack[-1]] < nums[i]:
            x = stack.pop()
            next_large[x] = i
        stack.append(i)

    return next_large

def print_list(nums):
    print(", ".join(map(str, nums)))

def main():
    nums = [73, 74, 75, 71, 69, 72, 76, 73]

    prev_less = find_prev_less(nums)
    next_less = find_next_less(nums)
    prev_large = find_prev_large(nums)
    next_large = find_next_large(nums)

    print_list(prev_less)
    print_list(next_less)
    print_list(prev_large)
    print_list(next_large)

if __name__ == "__main__":
    main()
