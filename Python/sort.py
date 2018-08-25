N = input()

a = raw_input()
a = a.split()
a = map(int, a)
maxi = a[0]
x = 0

for i in range(len(a)):
	for j in range(i+1, len(a)):
		if(a[i] > a[j]):
			temp = a[i]
			a[i] = a[j]
			a[j] = temp


print str(a)