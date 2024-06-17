def gcd(a, b):
    if(a > b):
        if(a % b):
            return gcd(b, a%b)
        else:
            return b
    else:
        if(b % a):
            return gcd(a, b%a)
        else:
            return a
