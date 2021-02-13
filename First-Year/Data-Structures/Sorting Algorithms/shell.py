def ShellSort(list):

    result = list.copy()
    n = len(list)
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
