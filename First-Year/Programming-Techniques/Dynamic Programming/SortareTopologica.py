f = open("/home/ddeliaioana/Documents/Python/ProgramareDinamica/graf.in", "r").read()
f = f.splitlines()
noduri = {}
n = 0
for i in f:
    nod = i.split(' ')
    nod1 = int(nod[0])
    nod2= int(nod[1])
    if nod1 > n:
        n = nod1
    elif nod2 > n:
        n = nod2
    if nod1 not in noduri:
        noduri[nod1] = [nod2]
    else:
        noduri[nod1] += [nod2]

a = [[0]*(n+1) for i in range(n+1)]

for i,j in noduri.items():
    for k in j:
        a[i][k] = 1

#q.pop(0)

def topsort():
    global a,n
    T = []
    q = []
    viz = [0] * (n+1)
    print(viz)
    gradint = [0] * (n+1)

    for i in range(1, n+1):
        for j in range(1, n+1):
            if a[i][j] == 1:
                gradint[j] = gradint[j] + 1

    for i in range(1,n+1):
        if gradint[i] == 0:
            q += [i]
            viz[i] = 1

    while q!=[]:
        nod = q[0]
        q.pop(0)
        T += [nod]
        for j in range(1,n+1):
            if a[nod][j] == 1 and viz[j] == 0:
                gradint[j] -= 1
                if gradint[j] == 0:
                    q += [j]
                    viz[j] = 1


    print(viz)
    return T

print(topsort())




