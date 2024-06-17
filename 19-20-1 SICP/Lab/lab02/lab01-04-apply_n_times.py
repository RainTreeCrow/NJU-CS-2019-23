def apply_n_times(f, n):
	def calc(x):
		for _ in range(0, n):
			x = f(x)
		return x
	return calc

# Why does the following code cause runtime error?
def apply_n_times_wrong(f, n):
    g = lambda x: x
    for _ in range(0, n):
        g = lambda x: f(g(x))
    return g

f = lambda x: (x + 1) * 2
print(apply_n_times(f, 3)(2))
print(apply_n_times_wrong(f, 3)(2))