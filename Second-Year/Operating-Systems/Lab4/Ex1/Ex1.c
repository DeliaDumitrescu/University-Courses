#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
	pid_t pid = fork();
	if(pid < 0)
		return errno;
	else if(pid == 0){
	// in child; getppid() -> pid of parent
		char *argv[] = {"ls", NULL};
		execve("/bin/ls", argv, NULL);
		perror(NULL);
	}
	else{
		printf("My PID = %d, Child PID = %d\n", getpid(), pid);
		wait(NULL);
		printf("Child %d finished \n", pid);
	}
	return 0;
}

