def number_of_two(n):
    num = 0;
    while (n>0):
        if n %10 == 2:
            num = num + 1
        n = n // 10
    return num
