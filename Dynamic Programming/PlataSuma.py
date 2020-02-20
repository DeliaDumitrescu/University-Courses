#Plata unei sume cu numar minim de bancnote date
f = open("/home/ddeliaioana/Documents/Python/ProgramareDinamica/bnc.in", "r").read()
f = f.splitlines()
s = int(f[0])
aux = [int(x) for x in f[1].split(',')]
b = sorted(aux, reverse = True)
inf = 1000000
sume = [inf]*(s+1)
sume[0] = 0
pred = [-1]*(s+1)
pred[0] = -1

for i in range(1, s+1):

    mini = inf
    last = -1

    for j in range(len(b)):
        if i - b[j] >= 0:
            if mini >  sume[i - b[j]]:
                mini = sume[i - b[j]]
                last = b[j]
    if mini != inf:
        sume[i] = 1 + mini
        pred[i] = last

while s > 0:
    print(pred[s])
    s = s- pred[s]

