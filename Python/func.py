

# for i in range(1,9):
# 	if(i == 1 | n/i == 0 & i != n):
# 		print "No"
# 		break
# 	else:
# 		print "Yes"


from math import sqrt
	
n = input()

def isPrime(x):
			if x == 1:
				return 'composite'
			for i in range(2, int(sqrt(x))+1):
					if(x%i == 0):
							return 'composite'
			return 'prime'

s = isPrime(n)
print s
