# Demo 1

5 * 2
5 ** 2 # Power operator
5 / 2 # True division, returns a number with a decimal component
5 // 2 # Floor division, rounds down to next smallest number


# Calculate circumference, area, volume of Earth
2 * 3.14159 * 3958.8 
3.14159 * 3958.8 * 2958.8
(4 / 3) * 3.141509 * 3958.8 * 3958.8 * 3958.8

# Assignment & importing names
radius = 3958.8
radius
2 * 3.14159 * radius
pi
from math import pi
2 * radius * pi
(4 / 3) * pi * (radius ** 3)

# Non-primitive expressions & assignment
circ = 2 * pi * radius
circ
vol = (4 / 3) * pi * (radius ** 3)
vol
vol / 2
circ * 6

# "Out of synch" assignment
radius = 2106.1
circ
vol, circ = (4/3) * pi * (radius ** 3), 2 * pi * radius
vol
circ

# Saving past assingments
mars_radius = radius
radius = 43441
mars_radius
radius

# Demo 2
radius = 10
vol = (4 / 3) * pi * (radius ** 3)
vol
radius = 20
vol

def volume(r):
    return (4 / 3) * pi * (r ** 3)

volume
volume(10)
volume(20)
volume(radius)
radius = 10
volume(radius)

def vol_ratio(r1, r2):
    return volume(r1) / volume(r2)

vol_ratio
vol_ratio(20, 10)
vol_Ratio(43441, 2106)

f = vol_ratio
f(20, 10)
vol_ratio = 10
f
vol_ratio
f(20, 10)
