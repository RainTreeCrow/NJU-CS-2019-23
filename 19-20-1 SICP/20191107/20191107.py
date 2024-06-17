def match_bracket(s: str) -> bool:
    brackets = {")": "(", "]": "[", "}": "{", ">": "<"}
    if len(s) == 0:
        return True
    else:
        b = []
        for bracket in s:
            if bracket in brackets.values():
                b.append(bracket)
            elif len(b) > 0 and b[-1] == brackets.get(bracket):
                b.pop()
            else:
                return False
        if len(b) > 0:
            return False
        else:
            return True


def left_or_right(s: str) -> str:
    left = ["q", "w", "e", "r", "t", "a", "s", "d", "f", "g", "z", "x", "c", "v", "b"]
    right = ["y", "u", "i", "o", "p", "h", "j", "k", "l", "n", "m"]
    num_left, num_right = 0, 0
    for letter in s:
        if letter in left:
            num_left += 1
        elif letter in right:
            num_right += 1
    if num_left > num_right:
        return "L"
    elif num_left < num_right:
        return "R"
    else:
        return "M"


def float2fraction(x: float) -> tuple:
    i = 2
    while int(i * x) != i * x:
        i += 1
    return int(i * x), i


def matrix_multiplication(A, B):
    n = len(A[0])
    C = []
    for i in range(len(A)):
        ci = []
        for j in range(len(B[0])):
            cij = 0
            for k in range(n):
                cij += A[i][k] * B[k][j]
            ci.append(cij)
        C.append(ci)
    return C


def fast_fibonacci(n: int) -> int:
    def matrix_mul(A, B):
        n = len(A[0])
        C = []
        for i in range(len(A)):
            ci = []
            for j in range(len(B[0])):
                cij = 0
                for k in range(n):
                    cij += A[i][k] * B[k][j]
                ci.append(cij)
            C.append(ci)
        return C

    def A_fac(n):
        last_A = [[1, 0], [0, 1]]
        A = [[1, 1], [1, 0]]
        while n > 0:
            if n % 2 == 1:
                last_A = matrix_mul(last_A, A)
                n -= 1
            A = matrix_mul(A, A)
            n //= 2
        return last_A

    return A_fac(n)[1][0]