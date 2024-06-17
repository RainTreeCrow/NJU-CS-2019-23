def is_triangle(a, b, c):
    if (a <= 0 or b <= 0 or c <= 0):
        return 0
    else:
        x = max(a, b, c)
        y = min(a, b, c)
        z = a + b + c - x -y
        if (y + z > x):
            return 1
        else:
            return 0
