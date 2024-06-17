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


# Please write your own code here.
def same_tree(t1, t2):
    if is_leaf(t1) and is_leaf(t2):
        if label(t1) == label(t2):
            return True
        else:
            return False
    elif is_leaf(t1) or is_leaf(t2):
        return False
    else:
        if label(t1) == label(t2):
            return same_tree(branches(t1), branches(t2))
        else:
            return False


print(same_tree(tree(1, [tree(2), tree(3)]), tree(1, [tree(2)])))