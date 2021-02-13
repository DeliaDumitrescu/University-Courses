"""e dă o mulțime de n cuburi. Fiecare cub este caracterizat prin lungimea laturii și culoare. Nu există
două cuburi având aceeași dimensiune. Fișierul “cuburi.txt” conține pe prima linie un număr natural
nenul n (numărul de cuburi), apoi pe următoarele n linii câte un număr natural nenul (lungimea laturii
cubului) și un șir de caractere (culoarea cubului).
Să se construiască un turn de înălțime maximă astfel încât peste un cub cu latura L și culoarea K se
poate așeza doar un cub cu latura mai mică strict decât L și culoare diferită de K. În fișierul “turn.txt”
să se afișeze componența turnului de la bază spre vârf, pe câte un rând latura și culoarea cubului, apoi
la final să se afișeze înălțimea totală a turnului."""
from operator import itemgetter

#latura strict mai mica deci merge cu dictionar
f = open("/home/ddeliaioana/Documents/Python/Greedy/cuburi.txt","r").read()
f = f.splitlines()
n = int(f[0])
v = []

for i in range(1,n+1):
    v += [[ x for x in f[i].split(' ')] ]

for i in range(0,n):
    v[i][0] = int(v[i][0])

print(v)
aux = sorted(v,key = itemgetter(0))
v = aux
v.reverse()

ind = 0
lastcolor = v[ind][1]
lastleng = v[ind][0]
height = v[ind][0]
print(str(height) + ' ' + lastcolor)
ind = 1

while ind < n :
    leng = v[ind][0]
    color = v[ind][1]
    if color != lastcolor and leng != lastleng:
        print(str(leng) + ' ' + color)
        lastcolor = color
        height += leng
    ind += 1

print(height)

