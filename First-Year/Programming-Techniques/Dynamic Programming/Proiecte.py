"""Se dau n activități prin timpul de început, timpul de sfârșit și profitul asociat desfășurării activității (n
intervale închise cu extremităţi numere reale care au asociate ponderi). Să se determine o submulțime de
activități compatibile (intervale disjuncte două câte două) care au profitul total maxim. Se va afişa
profitul total."""
f = open("/home/ddeliaioana/Documents/Python/ProgramareDinamica/bnc.in", "r").read()
f = f.splitlines()
n = len(f)
aux = []
p = []
cmax = [0]*(n+1)
ult = [0]*(n+1)

for i in f:
    aux.append([int(x) for x in i.split(' ')])
p = sorted(aux, key = lambda x:x[1])
p = [[0,0,0]]+p

for i in range(2,n+1):

    nrord = 0
    start = p[i][0]   #incep pr de progr

    for j in range(1, i):
        final = p[j][1]
        if start >= final:
            nrord = j

    ult[i] = nrord




for i in range(1, n+1):
    cmax[i] = max(cmax[i-1], p[i][2] + cmax[ult[i]])


print(cmax)