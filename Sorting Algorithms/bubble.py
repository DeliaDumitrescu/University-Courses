def BubbleSort(list):

    result = list.copy()
    n = len(list)

    for i in range(n): #ducem fiecare pe poz lui
        swp = 0

        for j in range(0, n - i -1): #ultimele i sortate

            if result[j] > result[j + 1]:
                result[j + 1], result[j] = result[j], result[j + 1]
                swp = 1

        if swp == 0:
            break

    return result