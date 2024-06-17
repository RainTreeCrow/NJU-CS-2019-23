# Sequence Aggregation

sum([1,2,3,4])

0 + 1 + 2 + 3 + 4

sum([1,2,3,4], 10)

10 + 1 + 2 + 3 + 4

# Will error:
#     sum([[1], [2], [3], [4]])
#     0 + [1] + [2] + [3] + [4]

sum([[1], [2], [3], [4]], [])

[] + [1] + [2] + [3] + [4]

# Will error:
#     sum(['a', 'b', 'c', 'd'], '')
''.join(['a', 'b', 'c', 'd'])

max([1, 2, 3, 4])

min([1, 2, 3, 4])

min([-4, -3, -2, -1, 0, 1, 2, 3, 4])

min([-4, -3, -2, -1, 0, 1, 2, 3, 4], key=lambda x: abs(x))

min([-2, -1, 0, 1, 2], key=lambda x: abs(x))

f = lambda x: abs(x)
f(-2)
f(-1)
f(0)
f(1)
f(2)

min([-2, -1, 0, 1, 2], key=abs)

# Will error:
#     min([(-2, 1), (-1, 2), (0, 3)], key=lambda x,y: y)
min([(-2, 1), (-1, 2), (0, 3)], key=lambda x: x[0])

max(1,2,3,4,5,6)

max(1,2,3,4,5,6,key=abs)


bool([])

bool([1])

bool('')

bool('a')

bool(1)

bool(0)

all([1, 2, 3, 4, 5])

all([1,2,3,0,4,5])

any([1,2,3,0,4,5])

any([0, False, ''])

any([0, False, '', 1])



# Trees


# Constructor
def tree(label, branches=[]):
    for branch in branches:
        assert is_tree(branch)
    return [label] + list(branches)

# Selectors
def label(tree):
    return tree[0]

def branches(tree):
    return tree[1:]

def is_tree(tree):
    if type(tree) != list or len(tree) < 1:
        return False
    for branch in branches(tree):
        if not is_tree(branch):
            return False
    return True

def is_leaf(tree):
    return not branches(tree)


ex1 = tree(8, [tree(4, [tree(2), tree(3)]), tree(3, [tree(1), tree(1, [tree(1), tree(1)])])])

def count_nodes(t):
    """
    >>> count_nodes(ex1)
    9
    """
    if is_leaf(t):
        return 1

    total = 0
    for b in branches(t):
        total += count_nodes(b)

    return total + 1

def count_nodes_alt(t):
    return sum([count_nodes_alt(b) for b in branches(t)]) + 1


ex2 = tree('D', [tree('B', [tree('A'), tree('C')]), tree('F', [tree('E'), tree('H', [tree('G'), tree('I')])])])

def collect_leaves(t):
    """
    >>> collect_leaves(ex2)
    ['A', 'C', 'E', 'G', 'I']
    """
    if is_leaf(t):
        return [label(t)]

    lst = []
    for b in branches(t):
        lst += collect_leaves(b)

    return lst

def collect_leaves_alt(t):
    if is_leaf(t):
        return [label(t)]

    return sum([collect_leaves_alt(b) for b in branches(t)], [])


def print_tree(t, indent=0):
    print(' '*indent, label(t)) 
    for b in branches(t):
        print_tree(b, indent + 1)


def print_calls(name, f):
    def new_f(t):
        print('Name:', name)
        print('Inputted Tree:')
        print_tree(t)
        input()
        ret = f(t)
        print('Returned:', ret)
        return ret
    return new_f

collect_leaves = print_calls('collect_leaves', collect_leaves)

def tiny_print(t):
    print('tree(', label(t), sep='', end='')
    
    if not is_leaf(t):
        print(', [', sep='', end='')
        for b in branches(t):
            tiny_print(b)
        print(']', sep='', end='')
    print(')', sep='', end='')
    


def square_tree(t):
    """
    >>> tiny_print(square_tree(tree(2)))
    tree(4)
    """
    if is_leaf(t):
        return tree(label(t)**2)

    lst = []
    for b in branches(t):
        lst += [square_tree(b)]

    return tree(label(t)**2, lst)


def fib_tree(n):
    """
    >>> print_tree(fib_tree(4))
     3
      1
       0
       1
      2
       1
       1
        0
        1
    """
    if n <= 1:
        return tree(n)

    left = fib_tree(n - 2)
    right = fib_tree(n - 1)
    return tree(label(left) + label(right), [left, right])
