fn three_sum_closest(nums: &mut Vec<i32>, target: i32) -> i32 {
    if nums.len() < 3 {
        return 0;
    }

    nums.sort();

    let mut closest = nums[0] + nums[1] + nums[2];

    for i in 0..nums.len() - 2 {
        let mut second = i + 1;
        let mut third = nums.len() - 1;

        while second < third {
            let sum = nums[i] + nums[second] + nums[third];
            if sum == target {
                return sum;
            }
            if (target - sum).abs() < (target - closest).abs() {
                closest = sum;
            } else if sum < target {
                second += 1;
            } else {
                third -= 1;
            }
        }
    }
    closest
}

fn main() {
    let mut nums = vec![-1, 2, 1, -4];
    let target = 1;

    println!("{}", three_sum_closest(&mut nums, target));
}
