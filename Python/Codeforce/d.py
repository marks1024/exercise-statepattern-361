file = open("gcd.in", "r")
a = file.readline()
a = a.split()
a = map(int, a)
m = min(a[0], a[1])


while(m != 0):
	if(a[0]%m == 0 and a[1]%m == 0):
					b = m
					break
	m-=1

result = open("gcd.out", "w")
result.write(str(b))

file.close()
result.close()