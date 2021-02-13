#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
//datele matricelor; pot fi citite de undeva
int a[2][3], b[3][4], multipl_matrix[2][4];
const int la = 2, ca = 3, lb = 3, cb = 4;

struct elem{
    int line, col;
};

void* multiply(void* args){
    struct elem *el = args;
    int *res = (int*)malloc(sizeof(int));
    for(int i = 0; i < la; i++)
        (*res) += a[el->line][i] * b[i][el->col];
    return res;
}

int main(int argc, char* argv[])
{
    int i, j, t = 0;
    int lr = la, cr = cb;
    pthread_t threads[la*cb];
    //initializam matricele random, pot fi si ele citite
    for(i = 0; i < la; i++)
        for(j = 0; j < ca; j++)
            a[i][j] = i + j;
    for(i = 0; i < lb; i++)
        for(j = 0; j < cb; j++)
            b[i][j] = i + j;

    for(i = 0; i < lr; i++)
        for(j = 0; j < cr; j++){
            struct elem *x = (struct elem*)malloc(sizeof(struct elem));
            x->line = i;
            x->col = j;
            pthread_create(&threads[t++], NULL, multiply, x);
        }

     void* ptr;
     t = 0;
     for(i = 0; i < lr; i++)
        for(j = 0; j < cr; j++){
            pthread_join(threads[t++], &ptr);
            multipl_matrix[i][j] = *(int*)ptr;
        }

    for(i = 0; i < lr; i++){
        for(j = 0; j < cr; j++){
            printf("%d ", multipl_matrix[i][j]);
        }
        printf("\n");
    }








    return 0;
}