#Sa se afiseze subsirul crescator de lungime maxima dintr-un sir de numere
f = open("/home/ddeliaioana/Documents/Python/ProgramareDinamica/bnc.in", "r").read()
v = [int(x) for x in f.split(' ')]
n = len(v)
lmax = [0]*n
pred = [0]*n

lmax[0] = 1
pred[0] = -1

def lungmax(x):
    global lmax,ind,v
    maxi = 0
    for i in range(0, x):
        if v[i] < v[x] and lmax[i] > maxi:
            maxi = lmax[i]
            ind = i
    return maxi

def lungmax2(x):
    global lmax,ind,v
    maxi = 0
    for i in range(x+1,n+1):
        if v[i]<v[x] and maxi < lmax[i]:
            maxi = lmax[i]
            ind = i
    return maxi


for i in range(1,n):
    ind = -1
    lmax[i] = 1 + lungmax(i)
    pred[i] = ind

print(lmax)
print(pred)