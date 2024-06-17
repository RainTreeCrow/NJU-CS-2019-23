# Call Expressions in Python
2019

2000 + 19

0 + 1 // 2 + 3 + 4 * ((5 // 6) + 7 * 8 * 9)

max(2, 4)

min(-2, 5000)

# Can't do +(1, 2)
from operator import add, mul

add(2, 3)

mul(2, 3)

max(1, 2, 3, 4, 5)

max(add(2, mul(4, 56)), add(3, 6))



# Functions, Values, Objects, Interpreters and Data
shakes = open('01 shakespeare.txt')

text = shakes.read().split()

text[:25]

len(text)

text.count('the')

text.count(',')

text.count(',') / len(text)

words = set(text)

'the' in words

len(words)

'draw'

'draw'[::-1]

{w for w in words if w == w[::-1] and len(w) > 4}

{w for w in words if w == w[::-1] and len(w) == 4}

{w for w in words if w == w[::-1] and len(w) == 5}

{w for w in words if w == w[::-1] and len(w) == 6}

{w for w in words if w == w[::-1] and len(w) == 7}

{w for w in words if w == w[::-1] and len(w) >= 7}

words = set(open('01 words').read().split())

len(words)

max(words, key=len)

max(words)

{w for w in words if w == w[::-1] and len(w) == 6}

{w for w in words if w == w[::-1] and len(w) > 6}

max({w for w in words if w[::-1] in words}, key=len)

len({w for w in words if w[0] == 'a'})

len({w for w in words if w[0] == 'A'})

lower = {w.lower() for w in words}

len({w for w in lower if w[0] == 'a'})

{w for w in words if w == w[::-1] and w < w[::-1] and len(w) > 6}

{w for w in words if w == w[::-1] and w <= w[::-1] and len(w) > 6}

{w for w in words if w[0] == 'A'}

{w for w in words if w[0] == 'A' and w.lower() in words}

max(words, key=lambda x: sum([1 for w in x if w in 'aeiou']))

max(words, key=lambda x: x.count('e'))

max(words, key=lambda x: x.count('x'))

max(words, key=lambda x: x.count('y'))

max([[max(words, key=lambda x: x.count(i))] for i in 'abcdefghijklmnopqrstuvvwxyzABCDEFGHIJKLMNOPQRSTUV'], key=len)

max(words, key=lambda x: x.count('a'))
