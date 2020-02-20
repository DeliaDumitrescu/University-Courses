f = open("/home/ddeliaioana/Documents/Python/ProgramareDinamica/bnc.in", "r").read()
f = f.splitlines()
ob = []
G = int(f[0])

for i in f:
        ob.append([int(x) for x in i.split(' ')])

del ob[0]

cmax = [ [0]*(G+1) for i in range(len(ob)+1)]

for i in range(1,len(ob)+1):
    for j in range(1,G+1):
        grob = ob[i-1][0]
        cob = ob[i-1][1]
        if grob > j:
            cmax[i][j] = cmax[i-1][j]
        else:
            cmax[i][j] = max( cmax[i-1][j], cob + cmax[i-1][j-grob])
for i in cmax:
    print(i)