def yang_tri(l, n):
    if(n > 0 and  n <= l):
        if(l == 1):
            return 1
        else:
            return yang_tri(l - 1, n - 1) + yang_tri(l - 1, n)
    else:
        return 0
