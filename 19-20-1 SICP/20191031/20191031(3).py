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
def leaf_sequence(t):
    sequence = []
    if is_leaf(t):
        sequence.append(label(t))
    else:
        for branch in branches(t):
            sequence.append(leaf_sequence(branch))

    def flatten(lst):
        flattened_list = []
        for i in lst:
            if isinstance(i, list):
                flattened_list.extend(flatten(i))
            else:
                flattened_list.append(i)
        return flattened_list

    return flatten(sequence)


print(leaf_sequence(tree(3, [tree(5, [tree(6), tree(2, [tree(7), tree(4)])]), tree(1, [tree(9), tree(8)])])))