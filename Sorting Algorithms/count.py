def CountSort(list):

    frecv = [0] * (max(list) + 1)
    result = []

    for i in list:
        frecv[i] += 1

    for i in range(0, max(list) + 1):
        for j in range(0, frecv[i]):
            if frecv[i] != 0:
                result += [i]

    return result