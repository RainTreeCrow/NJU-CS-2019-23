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
def max_and_min_height(t):
    def max_height(t):
        if is_leaf(t):
            max_t = 0
        else:
            max_b = []
            for branch in branches(t):
                max_b.append(max_height(branch))
            max_t = max(max_b) + 1
        return max_t

    def min_height(t):
        if is_leaf(t):
            min_t = 0
        else:
            min_b = []
            for branch in branches(t):
                min_b.append(min_height(branch))
            min_t = min(min_b) + 1
        return min_t

    return (max_height(t), min_height(t))


print(max_and_min_height(tree('A', [tree('B', [tree('E'),tree('F'),tree('G', [tree('K'),tree('L'),tree('M')])]), tree('C'), tree('D', [tree('H'), tree('I'), tree('J')])])))