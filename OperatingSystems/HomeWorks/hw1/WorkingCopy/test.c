#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

int main()
{
	int p[2],status;
	pid_t child1;
	char *cmd1[20] = {"ls",NULL};
	char *cmd2[20] = {"less",NULL};

	pid_t child = fork();

	if(child==0)
	{
		pipe(p);
		pid_t childInner = fork();

		if(childInner==0)
		{
			dup2(p[1],1);
			close(p[1]);
			close(p[0]);
			execvp("ls",cmd1);
		}
		else
		{
			pid_t a = wait(&status);
			dup2(p[0],0);
			close(p[0]);
			close(p[1]);
			execvp("less",cmd2);
		}
		return 0;
	}

	waitpid(child1, &status, WUNTRACED);
}