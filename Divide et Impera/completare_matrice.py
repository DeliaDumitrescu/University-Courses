"""Se citește de la tastatură un număr natural N. Se consideră o tablă (matrice) pătratică de
dimensiuni 2 N *2 N pe care se scriu numerele naturale de la 1 si 2 N *2 N prin vizitarea recursivă a
celor patru cadrane ale tablei în ordinea indicată și în figura alăturată: dreapta-sus, stânga-jos,
stânga-sus, dreapta-jos. De exemplu, daca N=2, tabla este completată astfel:
11 9 3 1
10 12 2 4
7 5 15 13
6 8 14 16
Să se afișeze în fișierul tabla.out matricea completată după regulile precizate."""
f = open("/home/ddeliaioana/Documents/Python/Divide_et_Impera/intrare.in", "r").read()
n = int(f)
m = [ [0] * (2**n) for i in range (2**n)]
val = 1

def compl(p2,i,j):

    global val,m

    if p2 == 1:
        m[i][j] = val
        val += 1
    else:
        compl( p2//2, i, j )
        compl( p2//2, i+p2//2, j-p2//2 )
        compl( p2//2, i, j-p2//2 )
        compl( p2//2, i+p2//2, j )

#compl(4,0,3)

def z_compl(p2,i,j):

    global val,m

    if p2 == 1:
        m[i][j] = val
        val +=1

    else:
        z_compl( p2//2, i, j )
        z_compl( p2//2, i, j + p2//2 )
        z_compl( p2//2, i + p2//2 , j )
        z_compl( p2//2, i + p2//2, j + p2//2 )


z_compl(4,0,0)
print(m)