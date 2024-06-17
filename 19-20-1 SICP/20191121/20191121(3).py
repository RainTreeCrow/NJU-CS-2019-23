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


def find_common(link1, link2):
    if link1 == link2:
        return link1.first
    else:
        rest_link1 = link1
        while rest_link1.rest is not Link.empty:
            rest_link1 = rest_link1.rest
            rest_link2 = link2
            while rest_link2.rest is not Link.empty:
                rest_link2 = rest_link2.rest
                if rest_link1 == rest_link2:
                    return rest_link1.first
    return -1