#Problema de nota 10
.data
 p:.word 4
 g:.word 4
 v:.space 400  #vectorul in care vom pune puterile lui g
 nu:.asciiz "p nu e prim"
 gen:.asciiz "Generatorul g este: "
 crpt:.asciiz "Mesajul criptat este: "
 dcrpt:.asciiz "Mesajul decriptat este: "
 sp:.asciiz " "
 end:.asciiz "\n"
 alfabet:.asciiz "ABCDEFGHIJKLMNOPQRSTUWVXYZ"
 msjclar:.space 20   #aici va fi sirul clar
 msjcodat: .space 20  #aici va fi sirul codat
 msjcriptat:.space 20    #aici va fi sirul criptat
 msjdecriptat: .space 20 #aici va fi sirul decriptat
 ch:.byte 'A'
.text

main:
#1.GASIRE GENERATOR
#CITIRE P
li $v0,5
syscall
move $t0,$v0
sw $t0,p

#CITIRE MESAJ CLAR
la $a0, msjclar     #adresa
li $a1, 20           # lung maxima a sirului
li $v0,8
syscall

#CITIRE MESAJ CRIPTAT
la $a0, msjcriptat   #adresa
li $a1, 20           # lung maxima a sirului
li $v0,8
syscall

lw $t0,p
ble $t0,1,neprim
beq $t0,2,prim

li $t1,2                #in $t1 tinem divizorii
div $t2,$t0,2       #in $t2 tinem p/2+1 unde ne oprim din cautare
addi $t2,1
loop_prim:
    beq $t1,$t2,prim
    rem $t3,$t0,$t1           #in $t3 tinem restul impartirii lui p la divizor
    beq $t3,$0,neprim       #daca restul e 0 p este prim
    addi $t1,1                    #crestem divizorul
    j loop_prim                  #continuam

prim:
 li $t1,1
 li $t2,0
 sw $t1,v($t2)    #punem 1 in prima casuta a vectorului pt g la 0
 li $t3,2              #in $t3 posibilii generatori, de la 2 incepem

 loop1:               #parcurg generatori 2->p-1

    li $t1,1          #setam i-ul in vector
    li $t2,4          #setam pozitia in memorie

    beq $t3,$t0,exit1          #am ajuns cu generatorul la p
    move $t4,$t3                 #in t4 copia lui t3

    loop2:    #completez vector cu puterile lui g, adica $t3

       beq $t1,$t0,exit2     #daca i=n am terminat de completat
       sw $t4, v($t2)        #accesam element

       mul $t4,$t4,$t3    #crestem puterea lui g
      rem $t4,$t4,$t0       #modulo p

       addi $t1,1
       addi $t2,4
       j loop2                    #continuam determinarea puterilor

    exit2:    #cand terminam de construit vectorul cu puteri, verificam daca generatorul e bun, cautand fiecare valoare 2→p-1 in vector (1 exista mereu, fiind g la 0)


         li $t1,2                                #in $t1 avem elementele de cautat in vector
         loop_val:
            beq $t1,$t0,gasitgen       #am terminat de cautat valorile deci am gasit generatorul
            li $t5,1                            #indicele din vector
            li $t6,4                            #indicele din memorie

            loop_vect:
                  beq $t5,$t0,nongasit      #am parcurs vectorul si nu am gasit valoarea
                  lw $t7,v($t6)
                  beq $t1,$t7,gasitval        #am gasit valoarea
                  addi $t5,1
                  addi $t6,4
                  j loop_vect

            gasitval:
                 addi $t1,1   #urmatoarea valoare de verificat in vector
                 j loop_val

           gasitgen:
               la $a0, gen
               li $v0, 4
               syscall

               move $a0,$t3  #afisam generatorul
               li $v0,1
               syscall

               la $a0,end
               li $v0,4
               syscall

               #2.CRIPTARE MESAJ CLAR
               li $t0, 0                      #sare din 1 in 1 pe loc.mem
               lb $t1, msjclar($t0)   #byte ul curent

               lb $t2,ch    #caracterul 'A'
               #in $t3 indicele byteului
               li $t4,4     #pt pozitia din memorie in vector
               li $t5,0     #indicele in msjcodat
               #in $t6 izomorfismul
               #in $t7 litera corespunzatoare izomorfismului

               loop_clar:
                    beqz $t1, exit_clar
                    lb $t1, msjclar($t0)   #accesare litera din sir citit

                    sub $t3,$t1,$t2         #$t3 indicele byte ului din $t1 (care trebuie inmultit cu 4)
                    mul $t3,$t3,$t4   #inmultire cu 4
                    lw $t6,v($t3)        #in $t6 il trecem in izomorfism
                    lb $t7,alfabet($t6)   #litera corespunzatoare izomorfismului
                    sb $t7,msjcodat($t5)   #punem litera gasita in vector

                    addi $t0,1
                    addi $t5,1
                    j loop_clar

            exit_clar:
                                              #afisare mesaj clar transformat in mesaj codat
               la $a0,crpt
               li $v0,4
               syscall

                   li $t0, 0                                 #sare din 1 in 1 pe loc.mem
                   lb $t1, msjcodat($t0)           #byte ul curent
                   sub $t5,$t5,2                   #scadem 2 din lungimea retinuta in $t5 pt newline si celalalt sir

                   loop_afis_codat:
                            beq $t0,$t5,exit_af
                            lb $t1, msjcodat($t0)

                             move $a0, $t1
                             li $v0, 11
                             syscall

                            addi $t0,1
                            j loop_afis_codat

                 exit_af:
        la $a0,end
        li $v0,4
        syscall
#3.DECRIPTARE MESAJ
 la $a0,dcrpt
 li $v0,4
 syscall
li $t0,0                      #sare din 1 in 1 pe loc.mem
lb $t1,msjcriptat($t0)           #byte ul curent
lb $t2,ch    #caracterul 'A'
#in $t3 indicele byteului
li $t5,0     #indicele in msjcriptat
#in $t6 izomorfismul
#in $t7 litera corespunzatoare izomorfismului

loop_criptat:
    beqz $t1, exit_criptat
    lb $t1, msjcriptat($t0)   #accesare litera din sir citit
    sub $t3,$t1,$t2      #$t3 indicele byte ului din $t1 al carui invers trebuie gasit

     lw $t7,p    #in $t7 p-ul
     li $t8,0    #indicele in vect
     li $t9,0    #indicele in mem
     loop_invers:
         beq $t8,$t7,exit_invers
         lw $t4,v($t9)
         beq $t3,$t4,gasit    #am gasit inversul lui $t3
         addi $t8,1
         addi $t9,4
         j loop_invers
    gasit:
    move $t6,$t8       #in $t6 il trecem in izomorfism invers
    exit_invers:
    lb $t7,alfabet($t6)   #litera corespunzatoare izomorfismului
    sb $t7,msjdecriptat($t5)   #punem litera gasita in vector

    addi $t0,1
    addi $t5,1
    j loop_criptat

exit_criptat:    #afisare mesaj criptat transformat in mesaj decriptat

li $t0, 0
lb $t1, msjdecriptat($t0)
sub $t5,$t5,1                        #scadem 1 din lungimea retinuta in $t5 pentru caracterul final
 loop_afis_criptat:
      beq $t0,$t5,exit_af2
      lb $t1, msjdecriptat($t0)

      move $a0, $t1
      li $v0, 11
      syscall

      addi $t0,1
      j loop_afis_criptat

 exit_af2:
      la $a0,end
      li $v0,4
      syscall

  b exit
  nongasit:

        addi $t3,1
         j loop1          #continuam cautarea de generatori

exit1:
b exit
neprim:

 la $a0,nu
 li $v0,4
 syscall
 b exit

exit:
li $v0,10
syscall

#Exemple date de intrare
#1). S-a citit p=7,  ACAD si BCF si s-a afisat:
#Generatorul g este: 3
#Mesajul criptat este: BCBG
#Mesajul decriptat este: ACF.
#2). S-a citit p=22 si s-a afisat: p nu este prim.
#3).S-a citit p=5, AAABC si DEDC si s-a afisat:
#Generatorul g este: 2
#Mesajul criptat este: BBBCE
#Mesajul decriptat este: DCDB.

#Descriere
#1). Cautam toti posibilii generatori incepand cu 2, punand intr-un vector puterile fiecarui posibil generator. Apoi, cautam secvential in vector fiecare valoare pentru a fi siguri ca s-au obtinut toate numerele din grup. La final, in vector vor fi puterile generatorului gasit.
#2). Pentru fiecare litera din mesajul clar, aflam indicele sau scazand codul lui ‘A’ (A va avea indicele 0, B va avea indicele 1 etc), il inmultim cu 4 pentru a-l putea cauta in vector si il trecem in izomorfismul corespunzator. Apoi, aflam litera corespunzatoare izomorfismului si o punem in vectorul de afisare.
#3). Pentru fiecare litera din mesajul criptat, aflam indicele literei, iar apoi cautam morfismul invers si aflam litera corespunzatoare, pe care o punem in vectorul de afisare.