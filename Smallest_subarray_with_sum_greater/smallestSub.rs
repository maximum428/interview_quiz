fn min_subarray_len(nums: &[i32], x: i32) -> Option<usize> {
    let mut start = 0usize;
    let mut sum = 0i32;
    let mut min_len = usize::MAX;
    
    for end in 0..nums.len() {
        sum += nums[end];
        
        while sum > x {
            min_len = min_len.min(end - start + 1);
            sum -= nums[start];
            start += 1;
        }
    }
    
    if min_len == usize::MAX {
        None
    } else {
        Some(min_len)
    }
}

fn main() {
    let nums1 = vec![1, 4, 45, 6, 0, 19];
    let x1 = 51;
    println!("{:?}", min_subarray_len(&nums1, x1));
    
    let nums2 = vec![1, 10, 5, 2, 7];
    let x2 = 9;
    println!("{:?}", min_subarray_len(&nums2, x2));
    
    let nums3 = vec![1, 2, 4];
    let x3 = 8;
    println!("{:?}", min_subarray_len(&nums3, x3));
}
