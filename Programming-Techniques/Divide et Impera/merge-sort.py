f1 = open("merge-test.in", "r").read()
f1 = f1.splitlines()

n = int(f1[0])
v = f1[1].split(' ')
v = [int(x) for x in v]

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

result = mergesort(v)

f2 = open("merge-test.out", "w+")
f2.write(' '.join(str(x) for x in result))
f2.close()



