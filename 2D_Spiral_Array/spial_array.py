def is_invalid(res, r, c):
    if r < 0 or c < 0 or r >= len(res) or c >= len(res) or res[r][c] != 0:
        return True
    return False

def get_spiral(n):
    if n <= 0:
        return [[]]

    res = [[0] * n for _ in range(n)]
    dc = [1, 0, -1, 0]
    dr = [0, 1, 0, -1]
    dir = 0
    val = 0
    r = 0
    c = 0
    limit = n * n

    while val < limit:
        val += 1
        res[r][c] = val
        r += dr[dir]
        c += dc[dir]

        if is_invalid(res, r, c):
            r -= dr[dir]
            c -= dc[dir]
            dir = (dir + 1) % 4
            r += dr[dir]
            c += dc[dir]

    return res

def main():
    vecs = get_spiral(8)

    for vec in vecs:
        print("\t".join(map(str, vec)))

if __name__ == "__main__":
    main()
