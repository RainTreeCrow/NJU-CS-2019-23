
def is_num(c):
    # 是否是数字
    return (c >= '0') and (c <= '9')

def is_capital(c):
    # 是否是大写字母
    return (c >= 'A') and (c <= 'Z')

def is_lower(c):
    # 是否是小写字母
    return (c >= 'a') and (c <= 'z')

def chop_num(s, i):
    num = 0
    while i < len(s):
        c = s[i]
        if (c >= 'A' and c <= 'Z') or (c >= 'a' and c <= 'z') or c == ')' or c == '(':
           return (num, i)
        else:
            num *= 10
            num += (int(c) - int('0'))
        i += 1
    return (num, i)

def chop_atom(fomula: str, i:int):
    atom_name = fomula[i]
    i += 1
    while i < len(fomula) and is_lower(fomula[i]):
        atom_name += fomula[i]
        i += 1
    
    if i >= len(fomula) or (fomula[i] == '(' or fomula[i] == ')' or is_capital(fomula[i])):
        return (atom_name, 1, i)
    else:
        count, i = chop_num(fomula, i)
        return (atom_name, count, i)

  


def count_atom(fomula: str):
    i = 0
    consl = []
    rec = []
    while i < len(fomula):
        if is_capital(fomula[i]):  # get an atom
            n, num, i = chop_atom(fomula, i)
            consl.append((n, num))
        elif fomula[i] == ')':
            i += 1
            if is_num(fomula[i]):
                num, i = chop_num(fomula, i)
                consl.append(-num)
                consl.insert(rec[len(rec) - 1], num)
                del rec[len(rec) - 1]
        elif fomula[i] == '(':
            i += 1
            rec.append(len(consl))
    return consl

def countOfAtoms(formula):
    s = {}
    l = count_atom(formula)
    times = 1
    for o in l:
        if type(o) == int:
            if o >= 0 :
                times *= o
            else:
                times //= -o
        else:
            n, num = o
            if n in s:
                s[n] += num*times
            else:
                s[n] = num*times
    ret = ''
    for o in sorted(s):
        ret += o
        if(s[o] != 1):
            ret += str(s[o])
    return ret

print(countOfAtoms('H2O'))
countOfAtoms('Mg(OH)2')
print(countOfAtoms('((N42)24(OB40Li30CHe3O48LiNN26)33(C12Li48N30H13HBe31)21(BHN30Li26BCBe47N40)15(H5)16)14'))
countOfAtoms('Ku12(H2(Mg(OH)2)2O2)2')
print(chop_atom('Ku12sdh', 0))





