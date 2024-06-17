# Print and None
-2

print(-2)

'Go Bears'

print('Go Bears')

None

print(None)

x = -2

x

x = print(-2)

x

print(x)

print(1, 2, 3)

print(None, None)

print(print(1), print(2))



# Nested Expressions with Print

print(1)

x = print(1)

print(x)

print(print(1))

y = print(2)

print(x, y)

print(print(1), print(2))



# Print vs Return

# Using return
def f():
    return 'stuff'

x = f()

x

'some ' + x

# Using print
def f():
    print('stuff')

x = f()

x

print(x)

'some ' + x



# if examples
def absolute_value(x):
    """
    >>> absolute_value(-2)
    2
    >>> absolute_value(2)
    2
    >>> sbsolute_value(0)
    0
    """
    if x > 0:
        return x
    elif x < 0:
        return -x
    else:
        return 0

def funky(x):
    """ Using elif

    >>> funky(-2)
    Negatory
    """
    if x < 0:
        print('Negatory')
    elif x % 2 == 0:
        return "I can't even"
    elif x % 3 == 0:
        return "3 of a kind"

def funky(x):
    """ Using if

    >>> funky(-2)
    Negatory
    "I can't even"
    """
    if x < 0:
        print('Negatory')
    if x % 2 == 0:
        return "I can't even"
    elif x % 3 == 0:
        return "3 of a kind"

def f(x):
    """
    >>> f(-1)
    'hi'
    >>> f(1)
    'bye'
    """
    if x < 0:
        return 'hi'
    else:
        return 'bye'

def g(x):
    """
    >>> g(-1)
    'hi'
    >>> g(1)
    'bye'
    """
    if x < 0:
        return 'hi'
    return 'bye'


def f():
    """
    >>> f()
    >>>
    """
    pass


def f():
    """
    >>> f()
    >>>
    """
    1

from operator import add
def f():
    add(1, 2)

f()

def f():
    print(1)
    print(2)
    return 3

f()

def f():
    return add(1, 2)

f()

def f():
    print(1)
print(2)

def g():
    print(1)
    print(2)

f()

g()




# Boolean Contexts
if 0:
    print('hi')

if 1:
    print('hi')



# Boolean Expressions
True and False

False and False

True and True

True or False

True or True

False or False

1 or True

0 or True

0 or False

False or 0

True and 5 + 2 and 8

True and False and 8

True and False and 8 and 1 and 3

False or print('hi') or True

False or print('hi') or False

True or print('hi') or True

True and print('hi') and True

True and not print('hi') and True

not True

not False

not 0

not 1

not None

not -1

False or True or print('hi')

False or True or 1 / 0



# Iteration
print(1)
print(2)
print(3)
print(4)
print(5)
print(6)
print(7)
print(8)
print(9)
print(10)

i = 0
while i < 10:
    i = i + 1
    print(i)


i, total = 0, 0
while i < 3:
    i = i + 1
    total = total + i

i = 0
while True:
    print(i)
    i = i + 1


def f(x):
    """
    >>> f(3)
    (3, 6)
    >>> f(4)
    (4, 10)
    >>> f(5)
    (5, 15)
    """
    i = 0
    total = 0
    while i < x:
        i = i + 1
        total = total + i
    return i, total



# Fibonacci
def fib(n):
    """
    >>> fib(0)
    0
    >>> fib(1)
    1
    >>> fib(2)
    1
    >>> fib(3)
    2
    >>> fib(4)
    3
    >>> fb(5)
    5
    """
    cur = 0
    nxt = 1

    i = 0
    while i < n:
        i = i + 1
        cur, nxt = nxt, cur + nxt

    return cur


