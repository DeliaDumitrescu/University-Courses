f = open("/home/ddeliaioana/Documents/Facultate/Sem2/Data Structures/date.in","r").read()
f = f.splitlines()
n = int(f[0])

from merge import MergeSort
from count import CountSort
from radix import RadixSort10, RadixSort256
from quick import QuickSort
from bubble import BubbleSort
from shell import ShellSort
from tools import test, time_to_execute, number_generator, too_big, print_data_set

for ind in range(1, n + 1):

    m, c, q, b, s, i, r = 1, 1, 1, 1, 1, 1, 1
    aux = f[ind].split(' ')
    how_many = int(aux[0])
    limit = int(aux[1])
    print_data_set(how_many, limit)

    v = number_generator(how_many, limit)

    if how_many > 10000:
        too_big(BubbleSort)
        too_big(ShellSort)
        b, s = 0, 0

    if how_many > 1000000:
        too_big(MergeSort)
        too_big(QuickSort)
        m, q = 0, 0

    if how_many > 100000000:
        too_big(sorted)
        too_big(CountSort)
        #too_big(RadixSort10)
        too_big(RadixSort256)
        i, c, r = 0, 0, 0

    if limit > 1000000:
        too_big(CountSort)
        c = 0

    if b == 1:
        time_to_execute(v, BubbleSort)

    if s == 1:
        time_to_execute(v, ShellSort)

    if m == 1:
        time_to_execute(v, MergeSort)

    if q == 1:
        time_to_execute(v, QuickSort)

    if c == 1:
        time_to_execute(v, CountSort)

    if r == 1:
        #time_to_execute(v, RadixSort10)
        time_to_execute(v, RadixSort256)

    if i == 1:
        time_to_execute(v, sorted)