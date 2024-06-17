#########
# Trees #
#########

def tree(label, branches=[]):
    for branch in branches:
        assert is_tree(branch), 'branches must be trees'
    return [label] + list(branches)

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

def print_tree(t, indent=0):

    print('  ' * indent + str(label(t)))
    for b in branches(t):
        print_tree(b, indent + 1)

def copy_tree(t):
    return tree(label(t), [copy_tree(b) for b in branches(t)])


# example trees:
t1 = tree(0, [tree(1), tree(2)])
t2 = tree(0, [t1, t1])

#recommend solution:
def same_tree1(t1, t2):
    return t1 == t2

print(same_tree1(t1,t2))
print(same_tree1(t1,t1))
# if it works, then it's enough for coding

def same_tree(t1,t2):
    if label(t1) == label(t2):
        if len(branches(t1)) != len(branches(t2)):
            return False
        for (b1,b2) in zip(branches(t1), branches(t2)):
            
            if not (same_tree(b1, b2)):
                return False
        return True
    else:
        return False
# just for practice!


def conv(p1, p2):
    max1, min1 = p1
    max2, min2 = p2
    maxx = max(max1, max2)
    minx = min(min1, min2)
    return (maxx, minx)

def max_min_depth(t, curd):
    if is_leaf(t):
        return (curd, curd)
    p = (0, 999)    # initially max 0, min 999. may wrong when min actually > 999
    for b in branches(t):
        p = conv(max_min_depth(b, curd+1), p)
    return p

def max_and_min_height(t):
    return max_min_depth(t, 0)

def leaf_sequence(t):
    if is_leaf(t):
        return [label(t)]
    l = []
    for b in branches(t):
        l += leaf_sequence(b)
    return l

    



