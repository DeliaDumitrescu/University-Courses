def RadixSort10(list):

    n = len(list)
    sublists = [ []*(n + 1) for i in range(10) ]
    maxi = max(list)
    exp = 1

    while maxi > 0:

        sublists = [ [] for i in range(10) ]

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

def RadixSort256(list):
    ind, exp = 0, 1

    while ind < 4:

        sublists = [ [] for i in range(257) ]

        for i in list:
            sublists[ (i//exp)  % 256] += [i]

        list = []

        for i in sublists:
            for j in i:
                if j != []:
                    list += [j]

        ind += 1
        exp = exp * 256

    return list


def RadixSort16(list):
    ind, exp = 0, 1

    while ind < 8:

        sublists = [ [] for i in range(17) ]

        for i in list:
            sublists[ (i//exp)  % 16] += [i]

        list = []

        for i in sublists:
            for j in i:
                if j != []:
                    list += [j]

        ind += 1
        exp = exp * 16

    return list
