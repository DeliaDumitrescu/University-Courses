f = open("/home/ddeliaioana/Documents/Python/Greedy/obiecte.txt","r").read()
f = f.splitlines()
n = int(f[0])
ob = []   #val/gr
obiecte = []

for i in range(1, n+1):
    ob.append([int(x) for x in f[i].split(' ')])

G = int(f[n+1])
castig = 0

for i in ob:
    obiecte += [i[0]/i[1]]


def pivot_mediana(v):

    if len(v) <= 5:
        return sorted(v)[len(v)//2]

    liste = [ sorted(v[i:i+5]) for i in range(0,len(v),5)]
    mijloace = [ l[len(l)//2] for l in liste]

    return pivot_mediana(mijloace)


def valoare(raport):
    for i in ob:
        if i[0]/i[1] == raport:
            return i[0]


def greutate(raport):
    for i in ob:
        if i[0]/i[1] == raport:
            return i[1]


def adaugobiecte(M):
    global castig
    global G
    for i in M:
        castig += valoare(i)
        G -= greutate(i)

def adaugrest(E):
    global castig
    global G
    i = 0
    while G > 0 and i < len(E) :

        if G - greutate(E[i]) >= 0:
            G -= greutate(E[i])
            castig += valoare(E[i])
        else:
            castig += E[i]*G
            G = 0

        i += 1

def alegere(v, fction):

    global G
    pivot = fction(v)
    print(pivot)

    L = [x for x in v if x < pivot]
    E = [x for x in v if x == pivot]
    M = [x for x in v if x > pivot ]

    if G < sum(M):
        alegere(M, pivot_mediana)

    elif G >= sum(M):
        adaugobiecte(M)
        adaugrest(E)
        if G > 0:
            alegere(L, pivot_mediana)

alegere(obiecte,pivot_mediana)
print(castig)