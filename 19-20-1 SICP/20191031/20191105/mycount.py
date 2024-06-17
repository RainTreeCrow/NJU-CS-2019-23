import collections

def count_of_atoms(formula):
    formula = "(" + formula + ")1"
    new_form = list()
    i = 0
    n = len(formula)
    while i < n:
        if i >= n:
            continue
        if formula[i].isupper():
            atom = formula[i]
            number = 0
            i += 1
            while i < n and formula[i].islower():
                atom += formula[i]
                i += 1
            while i < n and formula[i].isdigit():
                number = 10 * number + int(formula[i])
                i += 1
            if number == 0:
                number = 1
            new_form.append((atom, number))
        elif formula[i] == "(":
            new_form.append("(")
            i += 1
        elif formula[i] == ")":
            times = 0
            i += 1
            while i < n and formula[i].isdigit():
                times = 10 * times + int(formula[i])
                i += 1
            count = collections.Counter()
            while new_form[-1] != "(":
                atom, number = new_form.pop()
                count[atom] += number * times
            if new_form[-1] == "(":
                new_form.pop()
            for a, num in count.items():
                new_form.append((a, num))
    result = ""
    for things in sorted(new_form):
        if things == "(":
            continue
        a, num = things
        if num == 1:
            result += a
        else:
            result += a + str(num)
    return result

print(count_of_atoms("H2O"))
print(count_of_atoms("Mg(OH)2"))
print(count_of_atoms("((F2G3)2W4)5(M3G4)3((F6W3)2M5)2"))