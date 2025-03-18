fn is_invalid(res: &Vec<Vec<i32>>, r: i32, c: i32) -> bool {
    r < 0 || c < 0 || r >= res.len() as i32 || c >= res.len() as i32 || res[r as usize][c as usize] != 0
}

fn get_spiral(n: i32) -> Vec<Vec<i32>> {
    if n <= 0 {
        return vec![vec![]];
    }

    let mut res = vec![vec![0; n as usize]; n as usize];
    let dc = vec![1, 0, -1, 0];
    let dr = vec![0, 1, 0, -1];
    let mut dir = 0;
    let mut val = 0;
    let mut r   = 0;
    let mut c   = 0;
    let limit = n * n;

    while val < limit {
        val += 1;
        res[r as usize][c as usize] = val;
        r += dr[dir];
        c += dc[dir];
        if is_invalid(&res, r, c) {
            r -= dr[dir];
            c -= dc[dir];
            dir = (dir + 1) % 4;
            r += dr[dir];
            c += dc[dir];
        }
    }
    res
}

fn main() {
    let vecs = get_spiral(8);

    for vec in vecs {
        for num in vec {
            print!("{}\t", num);
        }
        println!();
    }
}
