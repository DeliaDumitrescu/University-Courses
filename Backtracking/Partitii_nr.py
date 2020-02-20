f = open("/home/ddeliaioana/Documents/Python/Backtracking/descompunere.in", "r").read()
f.splitlines()
#n = int(f[0])
n = 5
sum = 0
sol = [0] * (n+2)


#TOATE MODALIT DE A-L SCRIE PE N CA SUMA DE NR
def back(k):
    global sum
    global sol

    if sum == n:
        print(sol[:k])

    for i in range(1, n-sum+1):

            sol[k] = i
            sum = sum + i
            back(k+1)
            sum = sum - i

#back(0)


#TOATE MODALIT DE A-L SCRIE PE N CA SUMA DE NR DIFERITE

def back(k):
    global sum,sol

    if sum == n:
        print(sol[1:k])

    for i in range(sol[k-1],n-sum+1):
        sol[k] = i
        if i not in sol[1:k]:
            sum = sum + i
            back(k+1)
            sum = sum - i

sol[0]=1
back(1)



def bkt(k):                 #altfel
    global sol,n

    for v in range (1, n-k+2) :
        sol[k] = v
        scrt = sum(sol[:k+1])
        if scrt<=n:
            if scrt == n:
                print(sol[:k+1])
            else:
                pass
#bkt(0)

def bkt_permutari(k):

    global sol,n

    if k == n:
        print(sol[:k])

    for i in range(1,n+1):
        sol[k] = i
        if i not in sol[:k]:
            bkt(k+1)

#bkt_permutari(0)