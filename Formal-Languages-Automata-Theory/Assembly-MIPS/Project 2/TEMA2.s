.data

  v:.word 1, 2, 3, 4, 5
  n:.word 5

.text

suma_patrate:

    subu $sp, 4             #Incarcari
    sw $fp, 0($sp)
    addi $fp, $sp, 4

    subu $sp, 4
    sw $ra, 0($sp)

    subu $sp, 4
    sw $s0, 0($sp)

# $sp:($s0 v)($ra v)($fp v)$fp:(x)

    lw $s0, 0($fp)                               #in s0 elem de adaug
    beqz $s0, exit_patrate                   #daca x = 0 oprim procedura
            bne $s0,$v1,adaug                       #adaug doar elem de la 1->elem-1
            j exit_adaug                            #daca ajung aici, sunt la primul pas(in $s0 am chiar valoarea elementului pentru care calculez suma patratelor), deci nu adaug la suma

    adaug:
        mul $t0,$s0,$s0   #element la patrat
                add $v0,$v0,$t0   #adaug la suma elementul la patrat

    exit_adaug:

    addi $s0, -1
    subu $sp, 4
    sw $s0, 0($sp)
    jal suma_patrate
    addu $sp, 4

    exit_patrate:                #Restaurari
    lw $s0, -12($fp)
    lw $ra, -8($fp)
    lw $fp, -4($fp)
    addu $sp, 12
    jr $ra


 modifica:

    subu $sp,4                    #Incarcari
    sw $fp,0($sp)
        addi $fp,$sp,4

        subu $sp,4
        sw $ra,0($sp)

        subu $sp,4
        sw $s0,0($sp)

        subu $sp,4
        sw $s1,0($sp)

         #$sp:($s1v)($s0v)($rav)($fpv)$fp:(*v)(n)

        lw $s0,0($fp)   #in $s0 avem v
        lw $s1,4($fp)   #in $s1 avem n
        beqz $s1,exit_modifica   #daca n=0 iesim

        #Inlocuim elementul din vector cu suma patratelor

        li $v0,0
        lw $t0,0($s0)       #in t0 elem din vect
        bgt $t0,$0,poz
        li $v0,0
        j next
        poz:
        move $v1,$t0      #pun in $v1 valoarea din vector pentru a compara in suma_patrate si a calcula suma patratelor numerelor strict mai mici ca aceasta valoare, nu mai mici sau egale

        subu $sp,4
        sw $t0,0($sp)

       jal suma_patrate
       next:
       addu $sp,4
       sw $v0,0($s0)       #schimb valoarea in vect

       addi $s0,4   #trec la urmatorul element
       addi $s1,-1  #scad numar elemente vector

       subu $sp,4
       sw $s1,0($sp)

        subu $sp,4
        sw $s0,0($sp)

       jal modifica
       addu $sp, 8

      exit_modifica:    #Restaurari
      lw $s1,-16($fp)
      lw $s0,-12($fp)
      lw $ra,-8($fp)
      lw $fp,-4($fp)
      addu $sp,16
      jr $ra

main:

    lw $t0,n
    subu $sp,4
    sw $t0,0($sp)

    la $t0,v
    subu $sp,4
    sw $t0,0($sp)

    jal modifica

    addu $sp,8

     #Afisare

    li $t0,0
    li $t1,0
    lw $t2,n
    loop:
        beq $t0,$t2,exit

        lw $a0,v($t1)
        li $v0,1
        syscall

        li $a0,' '
        li $v0,11
        syscall

        addi $t0,1
        addi $t1,4
        j loop

        exit:

       li $v0,10
       syscall










