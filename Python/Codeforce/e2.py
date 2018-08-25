file = open("fib.in", "r")
a = file.read()
a = a.split()
a = map(int, a)
n = a[0]

for i in range(n+1):
	if(i ==0 or i ==1):
		fib = 1
		prev1 = fib
	elif(i == 2):
		prev2 = fib
		fib = prev1 + fib
	else:
		prev2 = prev1
		prev1 = fib
		fib = prev1 + prev2
		
result = open("fib.out", "w")
result.write(str(fib))

file.close()
result.close()