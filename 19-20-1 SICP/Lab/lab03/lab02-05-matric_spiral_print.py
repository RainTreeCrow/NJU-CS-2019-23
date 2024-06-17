def matric_spiral_print(l):
    w = len(l[0])
    h = len(l)
    r = 0
    c = 0
    while(h > 0 and w > 0):
        for i in range(c, c + w):
            print(l[r][i], end = ' ')
            
        if(h > 1) :
            for i in range(r + 1, r + h):
                print(l[i][c + w - 1], end = ' ')

        if(h > 1 and w > 1) :
            for i in range(c + w - 1, c, -1):
                print(l[r + h - 1][i - 1], end = ' ')

        if(h > 1 and w > 1) :
            for i in range(r + h - 2, r, -1):
                print(l[i][c], end = ' ')
                
        c += 1
        w -= 2
        h -= 2
        r += 1
