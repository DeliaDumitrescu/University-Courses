"""Fișierul “spectacole.txt” conține pe prima linie valoarea n, reprezentand numărul total de spectacole, iar apoi, pe câte un rând, ora de început și ora de sfârșit a câte unui spectacol.Să se programeze într-o singură sală un număr maxim de spectacole care să nu se suprapună. În
fișierul “spectacole.out” să se afișeze numărul de spectacole programate."""

from operator import itemgetter
f = open("/home/ddeliaioana/Documents/Python/Greedy/spectacole.in").read()
aux = f.splitlines()
n = int(aux[0])
hours = [ ]

for i in range(1, n+1):
    val = aux[i].split(' ')
    start = val[0]+ ':' +val[1]
    end = val[2] + ':' + val[3]
    hours.append([start,end])

sortedhours = sorted(hours, key = itemgetter(1))

last = sortedhours[0][1]
nr = 1

for i in range(1, n):
    start = sortedhours[i][0]
    end = sortedhours[i][1]
    if start >= last :
        nr += 1
        last = end

g = open("/home/ddeliaioana/Documents/Python/Greedy/spectacole.out","w")
g.write(str(nr))
