fn backtrack(nums: &Vec<i32>, res: &mut Vec<Vec<i32>>, vec: &mut Vec<i32>, target: i32, value: i32, start: i32) {
    if vec.len() == 4 && value == target {
        res.push(vec.clone());
        return;
    }

    for i in start..nums.len() as i32 {
        if i > start && nums[i as usize] == nums[(i-1) as usize] {
            continue;
        }
        vec.push(nums[i as usize]);
        backtrack(nums, res, vec, target, nums[i as usize]+value, i+1);
        vec.pop();
    }
}

fn three_sum2(nums: Vec<i32>, target: i32) -> Vec<Vec<i32>> {
    let mut res = Vec::new();
    let mut vec = Vec::new();
    let mut nums_ = nums;
    nums_.sort();
    backtrack(&nums_, &mut res, &mut vec, target, 0, 0);
    res
}

fn three_sum1(nums: Vec<i32>, target: i32) -> Vec<Vec<i32>> {
    let mut res = Vec::new();
    let mut nums_ = nums;
    if nums_.len() < 4 {
        return res;
    }
    nums_.sort();

    for i in 0..nums_.len() - 3 {
        if i > 0 && nums_[i] == nums_[i-1] {
            continue;
        }
        for j in i+1..nums_.len() - 2 {
            if j > i+1 && nums_[j] == nums_[j-1] {
                continue;
            }
            let mut third = j + 1;
            let mut four = nums_.len() - 1;
            while third < four {
                let sum = nums_[i] + nums_[j] + nums_[third] + nums_[four];
                if sum < target {
                    third += 1;
                } else if sum > target {
                    four -= 1;
                } else {
                    res.push(vec![nums_[i], nums_[j], nums_[third], nums_[four]]);
                    while third < four && nums_[third] == nums_[third+1] {
                        third+= 1;
                    }
                    while third < four && nums_[four] == nums_[four-1] {
                        four -= 1;
                    }
                }
            }
        }
    }
    res
}

fn print_result(vecs: Vec<Vec<i32>>) {
    for vec in vecs {
        print!("[");
        for num in vec {
            print!("{} ", num);
        }
        println!("]");
    }
}

fn main() {
    let nums = vec![1, 0, -1, 0, -2, 2];
    let target = 0;

    let res1 = three_sum1(nums.clone(), target);
    print_result(res1);

    let res2 = three_sum2(nums.clone(), target);
    print_result(res2);
}
