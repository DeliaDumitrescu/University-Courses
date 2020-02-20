t = 'kitten'
s = 'sitting'
ls = len(s)
lt = len(t)
L = [[0]*(ls+1) for i in range(lt+2)]
print(L)
for i in range(0, ls+1):
    for j in range(0, lt+1):
        if min(i,j) == 0:
            L[i][j] = max(i,j)
        else:
            if s[i-1] == t[j-1]:
                adaug = 0
            else:
                adaug = 1

            L[i][j] = min(min(L[i-1][j]+1,L[i][j-1]+1),L[i-1][j-1]+adaug)


for i in L:
    print(i)