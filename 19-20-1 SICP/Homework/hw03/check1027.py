def mobile(left, right):
    """Construct a mobile from a left side and a right side."""
    assert is_side(left), "left must be a side"
    assert is_side(right), "right must be a side"
    return ['mobile', left, right]


def is_mobile(m):
    """Return whether m is a mobile."""
    return type(m) == list and len(m) == 3 and m[0] == 'mobile'


def left(m):
    """Select the left side of a mobile."""
    assert is_mobile(m), "must call left on a mobile"
    return m[1]


def right(m):
    """Select the right side of a mobile."""
    assert is_mobile(m), "must call right on a mobile"
    return m[2]


def side(length, mobile_or_weight):
    """Construct a side: a length of rod with a mobile or weight at the end."""
    assert is_mobile(mobile_or_weight) or is_weight(mobile_or_weight)
    return ['side', length, mobile_or_weight]


def is_side(s):
    """Return whether s is a side."""
    return type(s) == list and len(s) == 3 and s[0] == 'side'


def length(s):
    """Select the length of a side."""
    assert is_side(s), "must call length on a side"
    return s[1]


def end(s):
    """Select the mobile or weight hanging at the end of a side."""
    assert is_side(s), "must call end on a side"
    return s[2]


def weight(size):
    """Construct a weight of some size."""
    assert size > 0
    return ['weight', size]


def size(w):
    """Select the size of a weight."""
    assert is_weight(w), 'must call size on a weight'
    return w[1]


def is_weight(w):
    """Whether w is a weight."""
    return type(w) == list and len(w) == 2 and w[0] == 'weight'


def examples():
    t = mobile(side(1, weight(2)),
               side(2, weight(1)))
    u = mobile(side(5, weight(1)),
               side(1, mobile(side(2, weight(3)),
                              side(3, weight(2)))))
    v = mobile(side(4, t), side(2, u))
    return (t, u, v)


def total_weight(m):
    """Return the total weight of m, a weight or mobile.

    >>> t, u, v = examples()
    >>> total_weight(t)
    3
    >>> total_weight(u)
    6
    >>> total_weight(v)
    9
    """
    if is_weight(m):
        return size(m)
    else:
        assert is_mobile(m), "must get total weight of a mobile or a weight"
        return total_weight(end(left(m))) + total_weight(end(right(m)))


def balanced(m):
    """
    not_balanced = 0
    if is_weight(end(left(m))):
        balance_l = size(end(left(m))) * length(left(m))
    else:
        if not balanced(end(left(m))):
            not_balanced += 1
        balance_l = total_weight(end(left(m))) * length(left(m))
    if is_weight(end(right(m))):
        balance_r = size(end(right(m))) * length(right(m))
    else:
        if not balanced(end(right(m))):
            not_balanced += 1
        balance_r = total_weight(end(right(m))) * length(right(m))
    if not_balanced == 0 and balance_l == balance_r:
        return True
    else:
        return False
    """

    not_balanced = 0
    balance_l = 0
    balance_r = 0
    if is_weight(end(left(m))) and is_weight(end(right(m))):
        balance_l = size(end(left(m))) * length(left(m))
        balance_r = size(end(right(m))) * length(right(m))
        if balance_l == balance_r:
            return True
        else:
            return False
    else:
        if not is_weight(end(left(m))):
            if not balanced(end(left(m))):
                not_balanced += 1
            balance_l = total_weight(end(left(m))) * length(left(m))
        if not is_weight(end(right(m))):
            if not balanced(end(right(m))):
                not_balanced += 1
            balance_r = total_weight(end(right(m))) * length(right(m))
        if not_balanced == 0 and balance_l == balance_r:
            return True
        else:
            return False