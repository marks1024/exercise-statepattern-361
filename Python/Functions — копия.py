N = input()

def factorial(x):
			ans = 1
			for i in range(1, x+1):
						ans = i
			return ans

answer = 0
for i in range(1, N+1):
	answer += 1.0/factorial(i)