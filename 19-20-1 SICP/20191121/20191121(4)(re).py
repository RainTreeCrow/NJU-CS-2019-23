def max_strings(x, y, z):
    def p(s):
        if len(s) <= 1:
            return [s]
        else:
            l = []
            abc = []
            for i in range(len(s)):
                if s[i] not in abc:
                    abc.append(s[i])
                    l.extend(s[i] + j for j in p(s[:i] + s[i + 1:]))
            return l

    if max(x, y, z) > 2 * (x + y + z - max(x, y, z) + 1):
        if x == max(x, y, z):
            x = 2 * (x + y + z - max(x, y, z) + 1)
        elif y == max(x, y, z):
            y = 2 * (x + y + z - max(x, y, z) + 1)
        else:
            z = 2 * (x + y + z - max(x, y, z) + 1)
    string = ''
    for _ in range(x):
        string += 'a'
    for _ in range(y):
        string += 'b'
    for _ in range(z):
        string += 'c'
    result = []
    lst = p(string)
    for it in lst:
        if 'aaa' not in it and 'bbb' not in it and 'ccc' not in it:
            result.append(it)
    return sorted(result)