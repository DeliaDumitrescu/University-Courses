"""În fișierul “harti.in” se află pe prima linie numărul natural n, urmat de valori i și j reprezentând 2
țări cu frontieră comună pe linii diferite. Afișează toate modalitățile în care pot fi colorate hărțile
astfel încât 2 țări cu graniță comună sa nu fie colorate identic"""

f = open("/home/ddeliaioana/Documents/Python/Backtracking/harti.in", "r").read()
f = f.splitlines()

#Colorare harti

n = int(f[0])
sol = [0] * (n+1)
tari = {}

for i in f:
    if i!=str(n):          #nu e prima linie
        nod = i.split(' ')
        nod1 = int(nod[0])
        nod2 = int(nod[1])
        if nod1 not in tari:
            tari[nod1] = [nod2]
        else:
            tari[nod1] += [nod2]

        if nod2 not in tari:
            tari[nod2] = [nod1]
        else:
            tari[nod2] += [nod1]


def valid(k):
    color = sol[k]
    for i in range(1, k):
        if sol[i] == color and i in tari[k]:
            return False
    return True


def back(k):
    global sol

    if k == n + 1 :
        print(sol[1:k])

    else:
        for i in range(1, 5):
            sol[k] = i
            if valid(k) == True:
                back(k+1)

back(1)
