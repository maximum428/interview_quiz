fn three_sum_smaller(nums: &mut Vec<i32>, target: i32) -> i32 {
    if nums.len() < 3 {
        return 0;
    }

    let mut count = 0;
    nums.sort();

    for i in 0..nums.len() - 2 {
        let mut second = i + 1;
        let mut third = nums.len() - 1;
        while second < third {
            let sum = nums[i] + nums[second] + nums[third];
            if sum < target {
                count += (third - second) as i32;
                second += 1;
            } else {
                third -= 1;
            }
        }
    }
    count
}

fn main() {
    let mut nums = vec![-2, 0, 1, 3];
    let target = 2;

    println!("{}", three_sum_smaller(&mut nums, target));
}
