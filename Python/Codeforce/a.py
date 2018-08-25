file = open("sum.in", "r")

a = file.readline()
a = a.split()
a = map(int, a)

b = a[0]+a[1]

fileq = open("sum.out", "w")
fileq.write(str(b))
fileq.close()
file.close()