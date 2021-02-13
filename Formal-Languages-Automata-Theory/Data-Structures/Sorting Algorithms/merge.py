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


def MergeSort(list):

    if len(list) <= 1:
        return list
    else:
        mid = len(list)//2
        left = MergeSort(list[:mid])
        right = MergeSort(list[mid:])
        return merge(left,right)

