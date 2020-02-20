"""Se considera un triunghi de numere naturale format din n lini. Prima linie contine un numar , a doua linie contine 3 numere si ultima linie contine n numere. Cu ajutorul acestui triunghi se pot forma sume de numere naturale in felul urmator. Se porneste cu numarul din linia 1, succesorul unui numar se afla pe linia urmatoare plasat sub el sau pe diagonala la dreapta. Care este cea mai mare suma care se poate forma astfel si care sunt numerele care il alcatuiesc?"""

f = open("/home/ddeliaioana/Documents/Python/ProgramareDinamica/tr.in", "r").read()
f = f.splitlines()
n = len(f)
tr = [ [0]*(n+1) for i in range(n)]

for i in range(len(f)):
    linie = f[i].split(' ')
    for j in range(len(linie)):
        tr[i][j+1] = int(linie[j])

smax = tr.copy()

for i in range(n-2,-1,-1):
    for j in range(1,i+2):
        smax[i][j] = tr[i][j] + max(smax[i+1][j],smax[i+1][j+1])
#print(smax[0][1])

def afisare(i,j):
    if i == n-1:
        print(smax[i][j])
        return
    else:
        print( smax[i][j] - max(smax[i+1][j],smax[i+1][j+1]),end=' ' )

        if smax[i+1][j] > smax[i+1][j+1]:
            afisare(i+1,j)
        else:
            afisare(i+1,j+1)

#afisare(0,1)
print(smax)
print(tr)