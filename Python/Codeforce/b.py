file = open("product.in", "r")
a = file.readline()
a = a.split()
a = map(int, a)
p = a[0]*a[1]

result = open("product.out", "w")
result.write(str(p))

file.close()
result.close()