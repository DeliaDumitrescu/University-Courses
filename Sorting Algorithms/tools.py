import time
import random
g = open("/home/ddeliaioana/Documents/Facultate/Sem2/Data Structures/date.out","w")

def test(result):

    corect = 1
    n = len(result)
    for i in range(0, n-1):
        if result[i] > result[i+1]:
            corect = 0
            break
    if corect == 0:
        g.write("Incorrect" + '\n')
    else:
        g.write("Correct" + '\n')


def time_to_execute(list, method):

    n = len(list)
    if method.__name__ == 'QuickSort':
        start_time = time.time()
        result = method(list, 0, n - 1, 0)
    else:
        start_time = time.time()
        result = method(list)

    end_time = time.time()

    if method.__name__ == 'sorted':
        g.write('Implemented sort' + '\n')
    else:
        g.write(method.__name__ + '\n')

    test(result)
    g.write("Execution Time: %s seconds" % (end_time - start_time) + '\n' + '\n')


def number_generator(how_many, limit):

    v = []
    for i in range(how_many):
        v += [random.randint(0, limit)]
    return v


def too_big(method):
        g.write(method.__name__ + '\n'+ "Can't sort!" + '\n' + '\n')

def print_data_set(how_many, limit):
     g.write("Pentru " + str(how_many) + " numere " + "mai mici ca " + str(limit) + ":" + '\n' + '\n')