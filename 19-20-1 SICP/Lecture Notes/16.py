################
# Linked Lists #
################

class Link:

    empty = ()

    def __init__(self, first, rest=empty):
        assert rest is Link.empty or isinstance(rest, Link)
        self.first = first
        self.rest = rest
                 

def sum_link(lnk):
    """ Returns the sum of elements in lnk """
    if lnk is Link.empty:
        return 0
    return lnk.first + sum_link(lnk.rest)


def display_lnk(lnk):
    """ Returns a string representing the
        non-empty linked list lnk """
    
    string = "< "

    while lnk is not Link.empty:
        if isinstance(lnk.first, Link):
            elem = display_lnk(lnk.first)
        else:
            elem = str(lnk.first)
        string += elem + " "
        lnk = lnk.rest

    return string + ">"



def map_lnk(f, lnk):
    
    if lnk is Link.empty:
        return Link.empty
    else:
        return Link(f(lnk.first), map_lnk(f, lnk.rest))
    
def map_iter(f, lnk):

    new_lnk = Link.empty
    while lnk is not Link.empty:
        new_lnk = Link(f(lnk.first), new_lnk)
        print(display_lnk(new_lnk))
        lnk = lnk.rest
    return new_lnk


lnk = Link(1, Link(2, Link(3)))




#########
# Trees #
#########

def tree(label, branches=[]):
    return [label] + list(branches)

def label(t):
    return t[0]

def branches(t):
    return t[1:]

class Tree:
    def __init__(self, label, branches=[]):
        for b in branches:
            assert isinstance(b, Tree)
        self.label = label
        self.branches = branches

    def is_leaf(self):
        return not self.branches

def print_tree(t, indent=0):
    print(" " * indent, t.label)
    for b in t.branches:
        print_tree(b, indent + 1)

def map(f, t):
    t.label = f(t.label)
    for b in t.branches:
        map(f, b)
        print("New tree")
        print_tree(b)
    
t = Tree(3, [Tree(2, [Tree(5)]), Tree(4)])
t2 = Tree(3, [Tree(1, [Tree(0), Tree(1)]),
              Tree(2, [Tree(1), Tree(1,
                                     [Tree(0), Tree(1)])])])
