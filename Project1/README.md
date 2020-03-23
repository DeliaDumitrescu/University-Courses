## Descriere

- Cautam toti posibilii generatori incepand cu 2, punand intr-un vector puterile fiecarui posibil generator. Apoi, cautam secvential in vector fiecare valoare pentru a fi siguri ca s-au obtinut toate numerele din grup. La final, in vector vor fi puterile generatorului gasit.

- Pentru fiecare litera din mesajul clar, aflam indicele sau scazand codul lui ‘A’ (A va avea indicele 0, B va avea indicele 1 etc), il inmultim cu 4 pentru a-l putea cauta in vector si il trecem in izomorfismul corespunzator. Apoi, aflam litera corespunzatoare izomorfismului si o punem in vectorul de afisare.

- Pentru fiecare litera din mesajul criptat, aflam indicele literei, iar apoi cautam morfismul invers si aflam litera corespunzatoare, pe care o punem in vectorul de afisare.

## Exemple date de intrare

- S-a citit p=7,  ACAD si BCF si s-a afisat:

Generatorul g este: 3 <br />
Mesajul criptat este: BCBG <br />
Mesajul decriptat este: ACF.

- S-a citit p=22 si s-a afisat: 

p nu este prim.

- S-a citit p=5, AAABC si DEDC si s-a afisat:

Generatorul g este: 2 <br />
Mesajul criptat este: BBBCE <br /> 
Mesajul decriptat este: DCDB.
