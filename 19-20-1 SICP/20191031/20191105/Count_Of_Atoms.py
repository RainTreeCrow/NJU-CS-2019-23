import collections


def count_of_atoms(formula):
    stack = list()
    formula = "(" + formula + ")1"
    i = 0
    n = len(formula)

    while i < n:
        if i >= n:
            continue
        if formula[i] == "(":
            stack.append("(")
            i += 1
        elif formula[i] == ")":
            parentNum = 0
            i += 1
            while i < n and formula[i].isdigit():
                parentNum = 10 * parentNum + int(formula[i])
                i += 1
            count = collections.Counter()
            while stack[-1] != "(":
                atom, atomNum = stack.pop()
                count[atom] += atomNum * parentNum
            if stack[-1] == "(":
                stack.pop()
            for c, t in count.items():
                stack.append((c, t))
        elif formula[i].isalpha():
            atom = formula[i]
            atomNum = 0
            i += 1
            while i < n and formula[i].isalpha() and formula[i].islower():
                atom += formula[i]
                i += 1
            while i < n and formula[i].isdigit():
                atomNum = 10 * atomNum + int(formula[i])
                i += 1
            atomNum = 1 if atomNum == 0 else atomNum
            stack.append((atom, atomNum))

    res = ""
    for atoms in sorted(stack):
        if atoms == "(":
            continue
        c, n = atoms
        if n == 1:
            res += c
        else:
            res += c + str(n)
    return res


print(count_of_atoms("H2O"))
print(count_of_atoms("Mg(OH)2"))
print(count_of_atoms("((F2G3)2W4)5(M3G4)3((F6W3)2M5)2"))