#Sa se afiseze lungimea subsirului comun de lungime maxima dintre doua cuvinte
s = 'subsir'
t = 'rustice'
ls = len(s)
lt = len(t)

lmax = [ [0]*(len(t)+1) for i in range(len(s)+1)]

for i in range(1,ls+1):
    for j in range(1,lt+1):
        if s[i-1] == t[j-1]:
            lmax[i][j] = 1 + lmax[i-1][j-1]
        else:
            lmax[i][j] = max(lmax[i-1][j],lmax[i][j-1])
for i in lmax:
    print(i)