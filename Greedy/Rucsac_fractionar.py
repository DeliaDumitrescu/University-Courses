f = open("/home/ddeliaioana/Documents/Python/Greedy/obiecte.txt","r").read()
f = f.splitlines()
n = int(f[0])
G = int(f[n+1])
ob = []          #[val, gr]

for i in range(1, n+1):
    aux = f[i].split(' ')
    ob.append([int(aux[0]), int(aux[1])])

obj = sorted(ob, key=lambda x:x[0]/x[1], reverse = True)

currentg = 0
i = 0
win = 0


while currentg <  G and i < n :
    g = obj[i][1]
    c = obj[i][0]
    if currentg + g <= G:
        currentg += g
        win += c
        #print(win)
    else:
        win += (c//g)*(G-currentg)
        break
    i += 1
f = open("/home/ddeliaioana/Documents/Python/Greedy/rucsac.txt","w")
f.write(str(win))



