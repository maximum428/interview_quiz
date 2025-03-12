def str_to_int(num):
    if len(num) == 0:
        return -1
    pos = 1
    res = 0
    for i in range(len(num) - 1, -1, -1):
        n = int(num[i])
        res += n * pos
        pos *= 10
    return res

if __name__ == "__main__":
    num_str = "356"
    print(str_to_int(num_str))
