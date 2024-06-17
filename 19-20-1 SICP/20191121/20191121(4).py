def max_strings(x, y, z):
    if x == 0 and y == 0 and z == 0:
        string = []
    elif y == 0 and z == 0:
        if x == 1:
            string = ['a']
        else:
            string = ['aa']
    elif x == 0 and z == 0:
        if y == 1:
            string = ['b']
        else:
            string = ['bb']
    elif x == 0 and y == 0:
        if z == 1:
            string = ['c']
        else:
            string = ['cc']
    elif x == 1 and y == 1 and z == 0:
        string = ['ab', 'ba']
    elif x == 1 and y == 0 and z == 1:
        string = ['ac', 'ca']
    elif x == 0 and y == 1 and z == 1:
        string = ['bc', 'cb']
    else:
        string = []
        if max(x, y, z) > 2 * (x + y + z - max(x, y, z) + 1) and x != 0 and y != 0 and z != 0:
            if x == max(x, y, z):
                x = 2 * (x + y + z - max(x, y, z) + 1)
            elif y == max(x, y, z):
                y = 2 * (x + y + z - max(x, y, z) + 1)
            else:
                z = 2 * (x + y + z - max(x, y, z) + 1)
        if x > 0:
            string_a = max_strings(x - 1, y, z)
            for item in string_a:
                if not (item[0] == 'a' and item[1] == 'a'):
                    string.append('a' + item)
                if not (item[-1] == 'a' and item[-2] == 'a'):
                    string.append(item + 'a')
        if y > 0:
            string_b = max_strings(x, y - 1, z)
            for item in string_b:
                if not (item[0] == 'b' and item[1] == 'b'):
                    string.append('b' + item)
                if not (item[-1] == 'b' and item[-2] == 'b'):
                    string.append(item + 'b')
        if z > 0:
            string_c = max_strings(x, y, z - 1)
            for item in string_c:
                if not (item[0] == 'c' and item[1] == 'c'):
                    string.append('c' + item)
                if not (item[-1] == 'c' and item[-2] == 'c'):
                    string.append(item + 'c')
    real_string = []
    max_len = 0
    for item in string:
        if len(item) > max_len:
            max_len = len(item)
    for item in string:
        if item not in real_string and len(item) == max_len:
            real_string.append(item)
    string = real_string
    return sorted(string)


print(max_strings(0, 3, 10))