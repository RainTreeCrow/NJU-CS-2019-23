import collections


def count_of_atoms(formula):
    dic, coeff, stack, elem, cnt, i = collections.defaultdict(int), 1, [], '', 0, 0
    for c in formula[::-1]:
        if c.isdigit():
            cnt += int(c) * (10 ** i)
            i += 1
        elif c == ')':
            stack.append(cnt)
            coeff *= cnt
            i = cnt = 0
        elif c == '(':
            coeff //= stack.pop()
            i = cnt = 0
        elif c.isupper():
            elem = c + elem
            dic[elem] += (cnt or 1) * coeff
            elem = ''
            i = cnt = 0
        elif c.islower():
            elem = c + elem
        return ''.join(k + str(v if v > 1 else '') for k, v in sorted(dic.items()))


print(count_of_atoms("H2O"))
print(count_of_atoms("Mg(OH)2"))
print(count_of_atoms("((F2G3)2W4)5(M3G4)3((F6W3)2M5)2"))