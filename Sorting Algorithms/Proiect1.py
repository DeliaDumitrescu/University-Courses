import time
f = open("/home/ddeliaioana/Documents/Facultate/Sem2/Data Structures/date.in","r").read()
g = open("/home/ddeliaioana/Documents/Facultate/Sem2/Data Structures/date.out","w")
f = f.splitlines()
n = int(f[0])
v = [ int(x) for x in f[1].split(' ')]


#1)
def merge(leftlist, rightlist):
    i = 0
    j = 0
    finallist = []

    while i < len(leftlist) and j < len(rightlist):
        if leftlist[i] <= rightlist[j]:
            finallist += [leftlist[i]]
            i += 1
        else:
            finallist += [rightlist[j]]
            j += 1


    finallist.extend(leftlist[i: ])
    finallist.extend(rightlist[j: ])

    return finallist


def mergesort(list):
    if len(list) <= 1:
        return list
    else:
        mid = len(list)//2
        left = mergesort(list[:mid])
        right = mergesort(list[mid:])
        return merge(left,right)
#

#2)

def countsort(list):
    frecv = [0] * (max(list) + 1)
    result = []
    for i in list:
        frecv[i] += 1
    for i in range(0, max(list) + 1):
        for j in range(0, frecv[i]):
            if frecv[i] != 0:
                result += [i]
    return result
#

#3).
def radixsort(list):
    maxi = max(list)
    result = []
    exp = 1
    l = [[0]*(len(list)) for i in range(10)]
    while maxi > 0:
        if exp == 1:
            for i in range(0, 10):
                l[i] = [x for x in list if (x//exp)%10 == i]

        else:
            l2 = [[0]*(len(list)) for i in range(10)]
            for i in range(0, 10):
                for j in l[i]:
                    l2[(j//exp)%10 ] += [j]

            l = l2.copy()

        exp = exp * 10
        maxi = maxi // 10


    for i in l:
        for j in i:
            if j != 0:
                result += [j]
    return result


#

#4)

def pivot(list, left, right):
    i = left
    j = right
    di = 0
    dj = 1

    while i < j:
        if list[i] > list[j]:
            list[i],list[j] = list[j],list[i]
            di,dj = dj,di

        i += di
        j -= dj

    return i


def quicksort(list, left, right, pas):

    global copylist
    if pas == 0:
        copylist = list.copy()
        pas = 1

    if left < right:
        x = pivot(copylist, left, right)
        quicksort(copylist, left, x - 1, pas)
        quicksort(copylist, x + 1, right, pas)
    return copylist
#

#5).

def bubblesort(list):
    result = list
    for i in range(n): #ducem fiecare pe poz lui
        swp = 0
        for j in range(0, n - i -1): #ultimele i sortate
            if result[j] > result[j + 1]:
                result[j + 1], result[j] = result[j], result[j + 1]
                swp = 1
        if swp == 0:
            break
    return result

#


#6).

def shellsort(list):
    result = list
    gap = len(result) // 2
    while gap > 0:
        for i in range(gap, n):

            to_move = result[i]
            j = i

            while j >= gap and to_move < result[j - gap]:
                result[j] = result[j - gap]
                j -= gap

            result[j] = to_move
        gap = gap // 2

    return result


def test(result):
    corect = 1
    for i in range(0, n-1):
        if result[i] > result[i+1]:
            corect = 0
            break
    if corect == 0:
        g.write("Incorrect" + '\n')
    else:
        g.write("Correct" + '\n')


def time_to_execute(list, method):

    if method.__name__ == 'quicksort':
        start_time = time.time()
        result = method(list, 0, n - 1, 0)
    else:
        start_time = time.time()
        result = method(list)

    end_time = time.time()

    g.write(method.__name__ + '\n')
    g.write(' '.join([str(x) for x in result]) + '\n')
    test(result)
    g.write("Execution Time: %s seconds" % (end_time - start_time) + '\n' + '\n')


time_to_execute(v, mergesort)
time_to_execute(v, countsort)
time_to_execute(v, radixsort)
time_to_execute(v, quicksort)
time_to_execute(v, bubblesort)
time_to_execute(v, shellsort)

