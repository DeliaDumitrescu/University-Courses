"""Fisierul s.txt contine pe prima linie valoarea n, reprezentand numarul total de spectacole, iar apoi, pe cate un rand, ora de inceput si ora de sfarsit pentru fiecare spectacol de la 1 la n. Se cere programarea spectacolelor folosind un numar minim de sali astfel incat spectacolele sa nu se suprapuna."""
from operator import itemgetter
f = open("/home/ddeliaioana/Documents/Python/Greedy/s.txt", "r").read()
f = f.splitlines()
n = int(f[0])

spectacole = []
sali = {}

for i in range(1,n+1):
    aux = f[i].split(' ')
    spectacole.append([aux[0],aux[1]])

ord = sorted(spectacole, key = itemgetter(0))


s = 1
sali[1] = ord[0][1]     #prima sala e ora la care se term primu sp
for k in range(1, n):

    start = ord[k][0]
    end = ord[k][1]

    for i,j in sali.items():
        if start >= j:
            sali[i] = end
            break
    else:
        s += 1
        sali[s] = end


for i in sali.keys():
    nrsali = i
print(nrsali)
