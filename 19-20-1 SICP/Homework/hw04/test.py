class Link:
    empty = ()

    def __init__(self, first, rest=empty):
        assert rest is Link.empty or isinstance(rest, Link)
        self.first = first
        self.rest = rest

    def __repr__(self):
        if self.rest is not Link.empty:
            rest_repr = ', ' + repr(self.rest)
        else:
            rest_repr = ''
        return 'Link(' + repr(self.first) + rest_repr + ')'

    def __str__(self):
        string = '<'
        while self.rest is not Link.empty:
            string += str(self.first) + ' '
            self = self.rest
        return string + str(self.first) + '>'


def remove_all(link, value):
    rest_link = link
    store = []
    while rest_link is not Link.empty:
        if rest_link.first != value:
            store.append(rest_link.first)
        rest_link = rest_link.rest
    i = len(store) - 1
    new_link = Link(store[i])
    i -= 1
    while i >= 0:
        new_link = Link(store[i], new_link)
        i -= 1
    link.first = new_link.first
    link.rest = new_link.rest


l1 = Link(0, Link(2, Link(2, Link(3, Link(1, Link(2, Link(3)))))))
print(l1)
remove_all(l1, 2)
print(l1)
remove_all(l1, 3)
print(l1)
remove_all(l1, 3)
print(l1)