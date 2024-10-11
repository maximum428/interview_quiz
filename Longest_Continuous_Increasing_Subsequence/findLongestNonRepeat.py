def findLongestNonRepeat(names):
    if len(names) < 2:
        return len(names)
    vec = [names[0]]
    res = 0
    start = 0
    for index, n in enumerate(names):
        if n not in vec:
            vec.append(n)
            res = max(res, index - start + 1)
        else:
            start = index
            vec = [names[index]]
    return max(res, index - start + 1)


if __name__ == "__main__":
    names = ["Alison", "Alina", "Alex", "Aileen", "Alex"];
    print(findLongestNonRepeat(names))
