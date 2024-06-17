############
# Nonlocal #
############

def make_withdraw(balance):
    def withdraw(amount):
        nonlocal balance
        if amount > balance:
            return "Insufficient funds"
        balance = balance - amount
        return balance
    return withdraw

##########
# Growth #
##########

total = 0

def count(f):
    """ Returns a version of f that counts the number of calls to that 
    function, and stores the value in the global variable total.

    You do not need to understand this implementation, and do not use the global
    keyword in your own code.

    Usage example: fact = count(fact). Calling fact after this will add the number
    of recursive calls to fact to the value of the total variable.
    """
    def counted_f(*args):
        global total
        total += 1
        return f(*args)
    return counted_f

def myfact(f, n):
    if n <= 1:
        return 1
    return n * f(f, n - 1)

def myfib(f, n):
    if n == 0:
        return 0
    if n == 1:
        return 1
    return f(f, n - 1) + f(f, n - 2)

def fact(n):
    if n <= 1:
        return 1
    return n * fact(n - 1)

def fib(n):
    if n == 0:
        return 0
    if n == 1:
        return 1
    return fib(n - 1) + fib(n - 2)
    
def fib_iter(n):
    """ An iterative version of fib that adds the number of times we go through
    the while loop to the total variable in the global frame
    """
    global total
    curr, nxt, i = 0, 1, 0
    while i < n:
        curr, nxt = nxt, curr + nxt
        i += 1
        total += 1
    return curr

memo = []

def memoized_fib(n):
    if n <= 1:
        return n
    if n > len(memo):
        memo.extend([-1 for _ in range(n + 1 - len(memo))])
    if memo[n] == -1:
        total = memoized_fib(n - 1) + memoized_fib(n - 2)
        memo[n] = total
    return memo[n]
            
    
