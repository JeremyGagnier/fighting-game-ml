import numpy

SIZE = 10
CHOICES = 36
MUTATION = 0.1

x = numpy.random.randint(CHOICES, size=SIZE, dtype=numpy.int8)
print(x)
y = numpy.random.randint(CHOICES, size=SIZE, dtype=numpy.int8)
print(y)
m = numpy.random.randint(CHOICES, size=SIZE, dtype=numpy.int8)
print(m)

choices = numpy.random.randint(2, size=SIZE, dtype=numpy.int8)
print(choices)

z = numpy.zeros(SIZE, numpy.int8)
z += numpy.multiply(x, choices)
z += numpy.multiply(y, 1 - choices)
print(z)


mutations = numpy.random.randint(int(round(1 / MUTATION)), size=SIZE, dtype=numpy.int32)
print(mutations == 0)

randoms = numpy.random.randint(CHOICES, size=SIZE, dtype=numpy.int8)
print(randoms)

z[mutations == 0] = randoms[mutations == 0]
print(z)

truth = numpy.logical_and((x == y), (x == m))

diff = sum(numpy.ones(SIZE, numpy.int8)[truth])
print(diff)
