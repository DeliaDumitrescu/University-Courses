import time
import random
f = open("/home/ddeliaioana/Documents/Facultate/Sem2/Data Structures/date.in","r").read()
g = open("/home/ddeliaioana/Documents/Facultate/Sem2/Data Structures/date.out","w")
f = f.splitlines()
n = int(f[0])



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

    n = len(list)
    sublists = [ []*(n + 1) for i in range(10) ]
    maxi = max(list)
    exp = 1

    while maxi > 0:

        sublists = [ []*(n + 1) for i in range(10) ]

        for i in list:
            sublists[ (i // exp) % 10] += [i]

        list = []

        for i in sublists:
            for j in i:
                    if j!=[]:
                        list += [j]
        maxi = maxi // 10
        exp = exp*10

    return list


#4)


def medianofthree(list, left, right):

    median = sorted([list[left], list[right], list[(left+right)//2]])[1]

    if median == list[left]:
        return left

    elif median == list[right]:
        return right

    return (left + right) // 2


def part(list, left, right):

    indexpivot = medianofthree(list, left, right)
    pivot = list[indexpivot]
    list[right], list[indexpivot] = list[indexpivot], list[right]

    i = left - 1

    for j in range(left, right):
        if list[j] <= pivot:
            i += 1
            list[i], list[j] = list[j], list[i]

    list[i + 1], list[right] = list[right], list[i + 1]

    return i + 1



def quicksort(list, left, right, pas):

    global copylist

    if pas == 0:
        copylist = list.copy()
        pas = 1

    if left < right:
        x = part(copylist, left, right)
        quicksort(copylist, left, x - 1, pas)
        quicksort(copylist, x + 1, right, pas)

    return copylist

#

#5).

def bubblesort(list):

    result = list.copy()

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

    result = list.copy()
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

def implementedsort(list):
    return sorted(list)


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
    test(result)
    g.write("Execution Time: %s seconds" % (end_time - start_time) + '\n' + '\n')


def number_generator(how_many, limit):

    v = []
    for i in range(how_many):
        v += [random.randint(0, limit)]
    return v


def too_big(method):
        g.write(method.__name__ + '\n'+ "Can't sort" + '\n' + '\n')



for i in range(1, n + 1):

    m,c,q,b,s=1,1,1,1,1

    aux = f[i].split(' ')
    how_many = int(aux[0])
    limit = int(aux[1])

    g.write("Pentru " + str(how_many) + " numere " + "mai mici ca " + str(limit) + ":" + '\n')

    v = number_generator(how_many, limit)

    if how_many > 5000000:
        too_big(mergesort)
        too_big(quicksort)
        too_big(countsort)
        m, q, c = 0, 0, 0

    if limit > 5000000:
        too_big(countsort)
        c = 0

    if how_many > 10000:
        too_big(bubblesort)
        too_big(shellsort)
        b, s = 0, 0

    if m == 1:
        time_to_execute(v, mergesort)

    if c == 1:
        time_to_execute(v, countsort)

    time_to_execute(v, radixsort)

    if q == 1:
        time_to_execute(v, quicksort)

    if b == 1:
        time_to_execute(v, bubblesort)

    if s == 1:
        time_to_execute(v, shellsort)

