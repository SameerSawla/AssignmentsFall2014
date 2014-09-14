#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

int main()
{
	int a;
	scanf("%d",&a);
	if(a==2)
	{
		pid_t pid = fork();
		if(pid<0)
		{
			printf("\nMAA CHUD GAI BE TERI");
			return 1;
		}
		else if(pid>0)
		{
			printf("\nYE HAI PITAJI");
		}
		else
		{
			printf("\nPEHLE CHILD PROCESS MEI WITH THE PID : %d",getpid());
			printf("\nFinal Value Hai %d\n",a*a);
		}
	}
	if(a==3)
	{
		pid_t pid = fork();
		if(pid<0)
		{
			printf("\nMAA CHUD GAI BE TERI");
			return 1;
		}
		else if(pid>0)
		{
			printf("\nYE HAI PITAJI");
		}
		else
		{
			printf("\nSECOND CHILD PROCESS MEI WITH THE PID : %d",getpid());
			printf("\nFinal Value Hai %d\n",a*a);
		}
	}
	return 0;
}