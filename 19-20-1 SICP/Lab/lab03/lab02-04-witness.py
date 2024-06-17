def wit_help(l, tallest, i):
    if(i < len(l)):
        if(l[i] > tallest):
            return wit_help(l, l[i], i + 1) + 1;
        else:
            return wit_help(l, tallest, i + 1);
    else:
        return 0
    

def witness(l):
    return wit_help(l, 0, 0)

