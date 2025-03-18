fn backtrack(nums: &Vec<i32>, res: &mut Vec<Vec<i32>>, vec: &mut Vec<i32>, value: i32, start: i32) {
    if vec.len() == 3 && value == 0 {
        res.push(vec.clone());
        return;
    }
    for i in start..nums.len() as i32 {
        if i > start && nums[i as usize] == nums[(i-1) as usize] {
            continue;
        }
        vec.push(nums[i as usize]);
        backtrack(nums, res, vec, value+nums[i as usize], i+1);
        vec.pop();
    }

}
fn three_sum1(nums: Vec<i32>) -> Vec<Vec<i32>> {
    let mut res = Vec::new();
    let mut vec = Vec::new();
    let mut _nums = nums;
    _nums.sort();
    backtrack(&_nums, &mut res, &mut vec, 0, 0);
    res
}

use std::cmp::Ordering;

fn three_sum2(nums: Vec<i32>) -> Vec<Vec<i32>> {
    let mut res = Vec::new();
    //let mut vec = Vec::new();
    let mut _nums = nums;

    _nums.sort();
    for mut i in 0.._nums.len() as i32 {
        let first = -_nums[i as usize];
        let mut second = i + 1;
        let mut third = _nums.len() as i32 - 1;

        while second < third {
            let sum = _nums[second as usize] + _nums[third as usize];
            match first.cmp(&sum) {
                Ordering::Greater => second += 1,
                Ordering::Less => third -= 1,
                Ordering::Equal => {
                    res.push(vec![_nums[i as usize], _nums[second as usize], _nums[third as usize]]);
                    while second < third && _nums[second as usize] == _nums[(second+1) as usize] {
                        second += 1;
                    }
                    while second < third && _nums[third as usize] == _nums[(third - 1) as usize] {
                        third -= 1;
                    }
                }
            }
        }
        while i + 1 < _nums.len() as i32 && _nums[i as usize] == _nums[(i+1) as usize] {
            i += 1;
        }
    }

    res
}

fn main() {
    let nums = vec![-1, 0, 1, 2, -1, -4];

    let res1 = three_sum1(nums.clone());
    for vec in res1 {
        println!("{:?}", vec);
    }
    
    let res2 = three_sum2(nums);
    for vec in res2 {
        println!("{:?}",vec);
    }
}
