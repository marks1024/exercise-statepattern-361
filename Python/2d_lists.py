n = 4
m = 4
a = [[1]*m for i in range(n)]
for i in range(len(a)):
		for j in range(len(a[i])):
			print(a[i][j], end = '')
		print()