
# def binarySearch(arr, n, s, e):

# 	# if(e-s+1 <= 0):
# 	# 	return 0
# 	# else:

# 		mid = s+((e-s)/2)
# 		if(arr[mid] == n):
# 			return mid
# 		elif(arr[mid] > n):
# 			return binarySearch(a, n, s, mid-1)
# 		else:
# 			return binarySearch(a, n, mid+1, e)
		
# a = [1, 2, 3, 4, 5]
# N = input()
# if(N>a[len(a)-1]):
# 	print "NO"
# else:
# 	pos = binarySearch(a, N, 0, len(a))
# 	print pos


# def binarySearch(arr, n, s, e):

# 	if(e >= 1):
# 		mid = s+((e-s)/2)
# 		if(arr[mid] == n):
# 			return mid
# 		elif(arr[mid] > n):
# 			return binarySearch(a, n, s, mid-1)
# 		else:
# 			return binarySearch(a, n, mid+1, e)
		
# a = [1, 2, 3, 4, 5]
# N = input()

# pos = binarySearch(a, N, 0, len(a)-1)
# print pos


# # def binarySearch(alist, item):
# # 	    if len(alist) == 0:
# # 	        return False
# # 	    else:
# # 	        midpoint = len(alist)//2
# # 	        if alist[midpoint]==item:
# # 	          return True
# # 	        else:
# # 	          if item<alist[midpoint]:
# # 	            return binarySearch(alist[:midpoint],item)
# # 	          else:
# # 	            return binarySearch(alist[midpoint+1:],item)
	
# # testlist = [0, 1, 2, 8, 13, 17, 19, 32, 42,]
# # print(binarySearch(testlist, 3))
# # print(binarySearch(testlist, 13))

# aList = [1,3,5,6,8,9,10,12,34,56,78,456]
# def recursiveBinarySearch(aList, target, start, end):
#     #aList = sorted(aList)

#     if end-start+1 <= 0:
#         return False
#     else:
#         midpoint = start + (end - start) // 2
#         if aList[midpoint] == target:
#             return midpoint
#         else:
#             if target < aList[midpoint]:
#                 return recursiveBinarySearch(aList, target, start, midpoint-1)
#             else:
#                 return recursiveBinarySearch(aList ,target, midpoint+1, end)

# print(recursiveBinarySearch(aList,500, 0, len(aList)))
my_list = [1, 3, 5, 7, 9, 11, 13, 15]
N = input()
def search(numbers, target, first, last):
    mid = (first + last) // 2
    if first > last:
        index = -1
    elif target == numbers[mid]:
        index =  mid
    elif target < numbers[mid]:
        index = search(numbers, target, first, mid-1)
    else:
        index = search(numbers, target, mid+1, last)
    return index

print(search(my_list, N, 0, len(my_list)-1))
#print(search(my_list, 10, 0, len(my_list)-1))