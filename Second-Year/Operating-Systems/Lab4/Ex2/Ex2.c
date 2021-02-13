#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
	int n;
	printf("Enter number\n");
	scanf("%d", &n);

	pid_t pid = fork();
	if(pid < 0)
		return errno;
	else if(pid == 0){
	//
		while(n != 1){
			printf("%d ", n);
			if(n % 2 == 1)
				n = 3 * n + 1;
			else
				n = n / 2;
		}
		printf("%d\n", 1);
		//exit(0);
	}
	else{
		wait(NULL);
		printf("Child %d finished \n", pid);

	}
	return 0;
}

