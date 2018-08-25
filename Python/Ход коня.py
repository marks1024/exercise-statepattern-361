
x1 = input()
x2 = input()
y1 = input()
y2 = input()

if x2 == x1 + 1 and y2 == y1 + 2:
	print('YES')
elif x2 == x1 - 1 and y2 == y1 - 2:
	print('YES')
elif x2 == x1 + 1 and y2 == y1 - 2:
	print('YES')
elif x2 == x1 - 1 and y2 == y1 + 2:
	print('YES')
elif x2 == x1 + 2 and y2 == y1 + 1:
	print('YES')
elif x2 == x1 - 2 and y2 == y1 - 1:
	print('YES')
elif x2 == x1 + 2 and y2 == y1 - 1:
	print('YES')
elif x2 == x1 - 2 and y2 == y1 + 1:
	print('YES')
else:
	print('NO')
