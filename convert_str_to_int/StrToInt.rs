fn str_to_int(num: &str) -> i32 {
    if num.len() == 0 {
        return -1;
    }
    let mut pos = 1;
    let mut res = 0;
    for c in num.chars().rev() {
        let n = c.to_digit(10).unwrap() as i32;
        res += n * pos;
        pos *= 10;
    }
    res
}

fn main() {
    let str = "356";
    println!("{}", str_to_int(str));
}
