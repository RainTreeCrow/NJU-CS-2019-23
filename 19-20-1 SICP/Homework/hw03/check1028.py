def tree(label, branches=[]):
    """Construct a tree with the given label value and a list of branches."""
    for branch in branches:
        assert is_tree(branch), 'branches must be trees'
    return [label] + list(branches)

def total_tree(m):
    def left_tree(m):
        if is_weight(end(left(m))):
            return tree(size(end(left(m))))
        else:
            return total_tree(end(left(m)))
    def right_tree(m):
        if is_weight(end(right(m))):
            return tree(size(end(right(m))))
        else:
            return total_tree(end(left(m)))
    return tree(size(end(left(m))) + size(end(right(m))), [left_tree(m), right_tree(m)])