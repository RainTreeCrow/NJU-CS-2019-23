# Generalization

from math import pi, sqrt

def area_square(r):
    assert r > 0, 'A length should be positive'
    return r * r

def area_circle(r):
    assert r > 0, 'A length should be positive'
    return r * r * pi

def area_hexagon(r):
    assert r > 0, 'A length should be positive'
    return r * r * 3 * sqrt(3) / 2


# Generalized Version
def area(r, shape):
    assert r > 0, 'A length should be positive'
    return r * r * shape

def area_square(r):
    return area(r, 1)

def area_crcle(r):
    return area(r, pi)

def area_hexagon(r):
    return area(r, 3 * sqrt(3) / 2)



# Generalization over Computational Processes
def sum_naturals(n):
    """Sum the first N naturals numbers.

    >>> sum_naturals(5)
    15
    """
    total, k = 0, 1
    while k <= n:
        total, k = total + k, k + 1
    return total

def sum_cubes(n):
    """Sum the first N cubes.

    >>> sum_cubes(5)
    225
    """
    total, k = 0, 1
    while k <= n:
        total, k = total + pow(k, 3), k + 1
    return total

# Generalized version
def summation(n, term):
    total, k = 0, 1
    while k <= n:
        total, k = total + term(k), k + 1
    return total

def identity(x):
    return x

def cube(x):
    return pow(x, 3)

def sum_naturals(n):
    return summation(n, identity)

def sum_cubes(n):
    return summation(n, cube)




# Functions as Return Values
def make_adder(n):
    """
    >>> add_two = make_adder(2)
    >>> add_two(3)
    5
    >>> add_two(10)
    12
    >>> add_two(add_two(2))
    6
    >>> make_adder(1)(2)
    3
    """
    def adder(k):
        return k + n
    return adder

def print_sums(n):
    """
    >>> print_sums(1)(2)(5)
    8
    >>> f = print_sums(1)
    1
    >>> f = f(2)
    3
    >>> f = f(3)
    6
    >>> f = f(4)
    10
    >>> f = f(5)
    15
    >>> f = f(6)
    21
    """
    print(n)
    def nex_sum(k):
        return print_sums(n + k)
    return next_sum
