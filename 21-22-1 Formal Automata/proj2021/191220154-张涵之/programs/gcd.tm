; This program calculates the gcd of two unary numbers.
; Input: two unary numbers seperated by 0's, e.g. '1111011111'

; the finite set of states
#Q = {0,cp1,sep,cp2,cmpr2l,erase2,erase3,goback2,goback3,illegal,found,illegal1,illegal2,illegal3,illegal4,illegal5,illegal6,illegal7,halt_accept,halt_reject}

; the finite set of input symbols
#S = {0,1}

; the complete set of tape symbols
#G = {0,1,_}

; the start state
#q0 = 0

; the blank symbol
#B = _

; the set of final states
#F = {halt_accept,halt_reject}

; the number of tapes
#N = 3

; the transition functions

; State 0: start state
0 1__ 1__ *** cp1
0 0__ 0__ *** illegal

; State cp1: copy the first number to the 2nd tape
cp1 1__ _1_ rr* cp1
cp1 0__ 0__ *** sep
cp1 ___ ___ *** illegal

; State sep: go through the 0's between the two numbers
sep 0__ ___ r** sep
sep 1__ 1__ *** cp2
sep ___ ___ *** illegal

; State cp2: copy the second number to the 3rd tape
cp2 1__ __1 r*r cp2
cp2 ___ ___ *ll cmpr2l
cp2 0__ 0__ *** illegal

; State cmpr2l: compare the 2nd and 3rd tape from right 2 left
cmpr2l _11 _11 *ll cmpr2l
cmpr2l _1_ _1_ *rr erase2
cmpr2l __1 __1 *rr erase3
cmpr2l ___ ___ *rr found

; State erase2: let the 2nd tape be num2 - num3
erase2 _11 __1 *rr erase2
erase2 ___ ___ *ll goback2

; State erase3: let the 3rd tape be num3 - num2
erase3 _11 _1_ *rr erase3
erase3 ___ ___ *ll goback3

; State goback3: move the index of 2 to the rightmost
goback2 __1 __1 *l* goback2
goback2 _11 _11 *** cmpr2l

; State goback3: move the index of 3 to the rightmost
goback3 _1_ _1_ **l goback3
goback3 _11 _11 *** cmpr2l

; State found: copy the result to the 1st tape
found _11 111 rrr found
found ___ ___ lll halt_accept

; State illegal: clear the 1st tape and write error msg
illegal 0__ ___ r** illegal
illegal 1__ ___ r** illegal
illegal ___ i__ r** illegal1
illegal1 ___ l__ r** illegal2
illegal2 ___ l__ r** illegal3
illegal3 ___ e__ r** illegal4
illegal4 ___ g__ r** illegal5
illegal5 ___ a__ r** illegal6
illegal6 ___ l__ *** halt_reject
