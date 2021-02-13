#Selectia celui de-al k minim (not finished)
import random

f = open("/home/ddeliaioana/Documents/Python/Divide_et_Impera/qs.in","r").read()
f = f.splitlines()
n = int(f[0])
k = int(f[1])
v = f[2].split(' ')
v = [int(x) for x in v]

def pivot_mediana(v):

    if len(v) <= 5:
        return sorted(v)[len(v)//2]

    liste = [ sorted(v[i:i+5]) for i in range(0,len(v),5)]
    mijloace = [ l[len(l)//2] for l in liste]

    return pivot_mediana(mijloace)

def quickselect(v, k, f_pivot ):
    pivot = f_pivot(v)

    L = [ x for x in v if x < pivot ]
    E = [ x for x in v if x == pivot]
    G = [ x for x in v if x > pivot]

    if k <= len(L):
        return quickselect(L, k, f_pivot)
    elif k <= len(L) + len(E) :
        return E[0]
    else:
        return quickselect(G, k - len(L) - len(E) ,f_pivot)

print(quickselect(v, k, pivot_mediana))
