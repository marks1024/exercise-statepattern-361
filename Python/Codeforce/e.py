file = open("fib.in", "r")
a = file.read()
a = a.split()
a = map(int, a)

def fibonacci(n):
			if(n==0):
				return 1
			if(n == 1):
				return 1
			return fibonacci(n-1) + fibonacci(n-2)

b = fibonacci(a[0])
	
result = open("fib.out", "w")
result.write(str(b))

file.close()
result.close()

