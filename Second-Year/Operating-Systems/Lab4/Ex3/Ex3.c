#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int n;

void collatz(int n)
{
    while(n != 1){
        printf("%d ", n);
        if(n % 2 == 1)
            n = 3 * n + 1;
        else
            n = n / 2;
        }
    printf("%d\n", 1);
}

int main()
{
    int i;
    printf("How many numbers do you want to process?");
    scanf("%d", &n);
    int *v = malloc(sizeof(int) * n);

    for(i = 0; i < n; ++i) {
        scanf("%d", &v[i]);
    }

    printf("Starting Parent %d\n", getpid());

    for(i = 0; i < n; ++i){
        pid_t pid = fork();
        if(pid < 0)
            perror("error");
        if(pid == 0){
            collatz(v[i]);
            printf("Done Parent %d Me %d\n", getppid(), getpid());
            exit(0);
        }
    }

    for(i = 0; i < n; i++)
        wait(NULL);

    printf("Done Parent %d Me %d\n", getppid(), getpid());


    return 0;
}
