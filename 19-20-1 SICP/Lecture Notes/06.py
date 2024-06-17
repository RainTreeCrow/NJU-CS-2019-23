from math import floor, sqrt 

def example(n):
    a = [True for _ in range(n)]
    for i in range(2, floor(sqrt(n)) + 1):
        if a[i]:
            j = i ** 2
        while j < n:
            a[j] = False
            j += i
    for i, b in enumerate(a):
        if b and i > 1:
            print(i)

def fact(n):
    """
    >>> fact(0)
    1
    >>> fact(1)
    1
    >>> fact(3) # 3 * 2 * 1
    6
    >>> fact(5)
    120
    """
    if n == 0:
        return 1
    else:
        return fact(n - 1) * n




def count_up(n):
    """
    >>> count_up(1)
    1
    >>> count_up(2)
    1
    2
    >>> count_up(4)
    1
    2
    3
    4
    """
    if n == 1:
        print(1)
    else:
        count_up(n - 1)
        print(n)
    



def sum_digits(n):
    """
    >>> sum_digits(9)
    9
    >>> sum_digits(19)
    10
    >>> sum_digits(2019)
    12
    """
    
    if n < 10:
        return n
    else:
        all_but_last, last = n // 10, n % 10
        return sum_digits(all_but_last) + last
   
