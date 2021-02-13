#n queen problem
n=8
regine=0

def verif_dama(i,j):
    for k in range(n):
        if k != i and table[k][j] == 1:
            return 0
        if k != j and table[i][k] == 1:
            return 0

        for l in range(n):
            if table[k][l] == 1 and k != i and l != j and abs(k - i) == abs(l - j):
                return 0
    return 1

def back(row,col):
    global regine
    if regine>n:
        return 0
    if col==n:
        if row==n-1:
            if regine==n:
                return 1
            return 0
        return back(row+1,0)

    table[row][col]=0

    total=back(row,col+1)

    table[row][col]=1

    if verif_dama(row,col)==1:
        regine += 1
        total+=back(row,col+1)
        regine -= 1

    table[row][col] = 0

    return total


table = [ [0]*n for i in range(n)]

print(back(0,0))
