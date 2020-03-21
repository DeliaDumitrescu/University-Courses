def randompivot(list, left, right):
    return list[random.randrange(left, right + 1)]

def medianofthree(list, left, right):

    middle = (left + right) // 2

    if(list[left] > list[middle]):
        list[left], list[middle] = list[middle], list[left]

    if(list[left] > list[right]):
        list[left], list[right] = list[right], list[left]

    if(list[middle] > list[right]):
        list[middle], list[right] = list[right], list[middle]

    return list[middle]

def medianoffive(list):
    return statistics.median([list[i] for i in range(0, len(list), len(list)//5 + 1)])


def QuickSort(list, left, right, pas):

    global copylist

    if pas == 0:
        copylist = list.copy()
        pas = 1

    i, j = left, right
    pivot = medianofthree(copylist, left, right)

    while i <= j:
        while copylist[i] < pivot:
            i += 1
        while copylist[j] > pivot:
            j -= 1

        if i <= j:
            copylist[i], copylist[j] = copylist[j], copylist[i]
            i += 1
            j -= 1

    if j > left:
        QuickSort(copylist, left, j, pas)
    if i < right:
        QuickSort(copylist, i, right, pas)

    return copylist