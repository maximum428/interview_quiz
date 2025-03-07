use std::vec::Vec;

fn find_prev_less(nums: &Vec<i32>) -> Vec<i32> {
    let size = nums.len();
    let mut prev_less = vec![-1; size];
    let mut stack = Vec::new();

    for i in 0..size {
        while let Some(&top) = stack.last() {
            if nums[top] > nums[i] {
                stack.pop();
            } else {
                break;
            }
        }
        prev_less[i] = if stack.is_empty() { -1 } else { stack[stack.len() - 1] as i32 };
        stack.push(i);
    }
    prev_less
}

fn find_next_less(nums: &Vec<i32>) -> Vec<i32> {
    let size = nums.len();
    let mut next_less = vec![-1; size];
    let mut stack = Vec::new();

    for i in 0..size {
        while let Some(&top) = stack.last() {
            if nums[top] > nums[i] {
                stack.pop();
                next_less[top] = i as i32;
            } else {
                break;
            }
        }
        stack.push(i);
    }
    next_less
}

fn find_prev_large(nums: &Vec<i32>) -> Vec<i32> {
    let size = nums.len();
    let mut prev_large = vec![-1; size];
    let mut stack = Vec::new();

    for i in 0..size {
        while let Some(&top) = stack.last() {
            if nums[top] < nums[i] {
                stack.pop();
            } else {
                break;
            }
        }
        prev_large[i] = if stack.is_empty() { -1 } else { stack[stack.len() - 1] as i32 };
        stack.push(i);
    }
    prev_large
}

fn find_next_large(nums: &Vec<i32>) -> Vec<i32> {
    let size = nums.len();
    let mut next_large = vec![-1; size];
    let mut stack = Vec::new();

    for i in 0..size {
        while let Some(&top) = stack.last() {
            if nums[top] < nums[i] {
                stack.pop();
                next_large[top] = i as i32;
            } else {
                break;
            }
        }
        stack.push(i);
    }

    next_large
}

fn print_list(nums: &Vec<i32>) {
    for & num in nums {
        print!("{}, ", num);
    }
    println!();
}

fn main() {
    let nums = vec![73, 74, 75, 71, 69, 72, 76, 73];

    let prev_less = find_prev_less(&nums);
    let next_less = find_next_less(&nums);
    let prev_large = find_prev_large(&nums);
    let next_large = find_next_large(&nums);

    print_list(&prev_less);
    print_list(&next_less);
    print_list(&prev_large);
    print_list(&next_large);
}
