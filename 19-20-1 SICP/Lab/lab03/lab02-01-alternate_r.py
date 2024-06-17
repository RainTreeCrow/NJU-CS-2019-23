def alternate_r(a, b):
    if(a > 0 or b > 0):
        return alternate_r(b//10, a)*10 + b%10
    else:
        return 0
