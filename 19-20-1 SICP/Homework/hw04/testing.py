class Tree:
    def __init__(self, label, branches=[]):
        for b in branches:
            assert isinstance(b, Tree)
        self.label = label
        self.branches = list(branches)

    def is_leaf(self):
        return not self.branches

    def map(self, fn):
        self.label = fn(self.label)
        for b in self.branches:
            b.map(fn)

    def __contains__(self, e):
        if self.label == e:
            return True
        for b in self.branches:
            if e in b:
                return True
        return False

    def __repr__(self):
        if self.branches:
            branch_str = ', ' + repr(self.branches)
        else:
            branch_str = ''
        return 'Tree({0}{1})'.format(self.label, branch_str)

    def __str__(self):
        def print_tree(t, indent=0):
            tree_str = '  ' * indent + str(t.label) + "\n"
            for b in t.branches:
                tree_str += print_tree(b, indent + 1)
            return tree_str

        return print_tree(self).rstrip()


def generate_paths(t, x):
    path = []
    marked = False

    def make_paths(t0, x0):
        nonlocal path, marked
        if x0 not in t0:
            return
        if marked:
            return
        if t0.label == x:
            path.append(t0.label)
            t0.label = str(t0.label)
            marked = True
            return
        if x0 in t0:
            path.append(int(t0.label))
            for b in t.branches:
                make_paths(b, x0)

    while x in t:
        path = []
        marked = False
        make_paths(t, x)
        yield path