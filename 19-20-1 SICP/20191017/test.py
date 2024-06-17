def alternate_r(a, b):
    if a < 10 and b < 10:
        return a * 10 + b
    else:
        return alternate_r(a // 10, b // 10) * 100 + alternate_r(a % 10, b % 10)


print(alternate_r(123, 321))


def gcd(a, b):
    if a < b:
        a = a + b
        b = a - b
        a = a - b
    if a % b == 0:
        return b
    else:
        return gcd(b, a % b)


print(gcd(16, 24))


def yang_tri(n, i):
    if i < 1 or i > n or n < 0:
        return 0
    elif n == 1 and i == 1:
        return 1
    else:
        return yang_tri(n - 1, i) + yang_tri(n - 1, i - 1)


print(yang_tri(3, 1))
print(yang_tri(7, 4))


def witness(list):
    if len(list) == 1:
        return 1
    else:
        if max(list[:-1]) < list[len(list) - 1]:
            return witness(list[:-1]) + 1
        else:
            return witness(list[:-1])


print(witness([1, 1, 2, 6, 4, 3]))

"""
import numpy as np
def matrix_spiral_print(matrix):
    count = 0
    total = len(matrix) * len(matrix[0])
    if 1 == len(matrix):
        for x in matrix[0]:
            print(x, end=' ')
    else:
        i = 0
        while i < len(matrix[0]):
            print(matrix[0][i], end=' ')
            count += 1
            i += 1
        j = 1
        while j < len(matrix):
            print(matrix[j][len(matrix[0]) - 1], end=' ')
            count += 1
            j += 1
        k = (len(matrix[0]) - 2)
        while k >= 0:
            print(matrix[len(matrix) - 1][k], end=' ')
            count += 1
            k -= 1
        l = (len(matrix) - 2)
        while l >= 1:
            print(matrix[l][0], end=' ')
            count += 1
            l -= 1
        if count != total:
            if len(matrix) >= 2:
                matrix = np.delete(matrix, [0, len(matrix) - 1], axis = 0)
            else:
                m = 0
                while m < len(matrix[0]):
                    print(matrix[0][m], end=' ')
                    m += 1
            if len(matrix[0]) >= 2:
                matrix = np.delete(matrix, [0, len(matrix[0]) - 1], axis = 1)
            else:
                n = 0
                while n < len(matrix):
                    print(matrix[n][0], end=' ')
            matrix_spiral_print(matrix)
"""

def print_matrix(i, j, m, n, m0, n0, matrix):
    if n == 0 or n == n0:
        while j <= m:
            print(matrix[i][j], end=' ')
            j += 1
    elif m == 0 or m == m0:
        while i <= n:
            print(matrix[i][j], end=' ')
            i += 1
    else:
        while j < m:
            print(matrix[i][j], end=' ')
            j += 1
        while i < n:
            print(matrix[i][j], end=' ')
            i += 1
        while j > m0:
            print(matrix[i][j], end=' ')
            j -= 1
        while i > n0:
            print(matrix[i][j], end=' ')
            i -= 1

def matrix_spiral_print(matrix):
    m = len(matrix[0]) - 1
    n = len(matrix) - 1
    i = 0
    j = 0
    m0 = 0
    n0 = 0
    print_matrix(i, j, m, n, m0, n0, matrix)
    while n - n0 >= 2 and m - m0 >= 2:
        i += 1
        j += 1
        m -= 1
        n -= 1
        m0 += 1
        n0 += 1
        print_matrix(i, j, m, n, m0, n0, matrix)