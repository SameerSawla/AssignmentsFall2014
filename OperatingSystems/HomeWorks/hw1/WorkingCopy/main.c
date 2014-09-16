#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>

#define BYE "Bye"
#define HISTORY "history"
#define EXIT "exit"
#define QUIT "quit"
#define true 1
#define false 0

void printHistory(char history[4][1000],int *historyPointerLocation, int *noOfElementsInHistory)
{		
	int lineNumber = 1;
 	int i=0;
 	if(*historyPointerLocation!=*noOfElementsInHistory)
 	{	
 		if(lineNumber<10)
 		{
 			printf("00%d\t%s\n",lineNumber,history[*historyPointerLocation]);
 		}
 		else
 		{
 			if(lineNumber<100)
 			{
 				printf("0%d\t%s\n",lineNumber,history[*historyPointerLocation]);
 			}
 			else
 			{
 				printf("%d\t%s\n",lineNumber,history[*historyPointerLocation]);
 			}
 		}
 		lineNumber = lineNumber + 1;
 		i = *historyPointerLocation+1;
 	}
 	
 	for(i;i!=*historyPointerLocation;i++)
 	{	
 		if(i>=*noOfElementsInHistory)
 		{

 			i=0;
 			if(i==*historyPointerLocation)
 			{	
 				break;
 			}
 		}
 		if(lineNumber<10)
 		{
 			printf("00%d\t%s\n",lineNumber,history[i]);
 		}
 		else
 		{
 			if(lineNumber<100)
 			{
 				printf("0%d\t%s\n",lineNumber,history[i]);
 			}
 			else
 			{
 				printf("%d\t%s\n",lineNumber,history[i]);
 			}
 		}
 		// printf("%d\t%s\n",lineNumber,history[i]);
 		lineNumber = lineNumber + 1;
 	}
}

char* searchHistoryUsingNumber(int number,int *historyPointerLocation,int *noOfElementsInHistory,char history[999][1000])
{
 if(number <= *noOfElementsInHistory)
 {	
	 if(*historyPointerLocation!=*noOfElementsInHistory)
	 {
	  number = number + *historyPointerLocation-1;
	 }

	 if(number>*noOfElementsInHistory)
	 {
	 	number = number - *noOfElementsInHistory;
	 }
 	 return history[number-1];
 }
 else
 {
 	return "";
 }
}

void executeWithAChildProcessBackground(char *input,char *tokens,char inputArray[][100],int inputArrayCount)
{
	printf("\nIn Background\n");
	pid_t pid;
	pid = fork();
	int n = strlen(input) + strlen(tokens);
	char full[n];
	strcpy(full,tokens);
	strcat(full,"/");
	strcat(full,input);
	if(pid<0)
	{
		perror("SamShell: ERROR : 'fork() failed");
		return EXIT_FAILURE;
	}
	if(pid==0) //Child Process
	{
		sleep(2);
		printf("\n");
		int rc;
		if(inputArrayCount>0)
		{
			rc = execlp(full,input,inputArray,NULL);
		}	
		else
		{
			rc = execlp(full,input,NULL);
		}
		perror("SamShell: ERROR : 'execlp() failed\n");

	}
	if(pid>0) //Parent process
	{
		printf("\n[process running in background with pid %d]\n",(int)pid);
		int status;
		int child_pid = waitpid(pid,&status,WNOHANG);
		if(child_pid>0)
		{
				if(WIFEXITED(status))
				{
				 printf("\n[process %d completed]\n",(int)pid);	
				}
		}	
		
	}
}

void executeWithAChildProcessForeground(char *input,char *tokens,char inputArray[][100],int inputArrayCount)
{	//input[1] = NULL;
	pid_t pid;
	pid = fork();
	int n = strlen(input) + strlen(tokens);
	char full[n];
	strcpy(full,tokens);
	strcat(full,"/");
	strcat(full,input);
	if(pid<0)
	{
		perror("SamShell: ERROR : 'fork() failed");
		return EXIT_FAILURE;
	}
	if(pid==0) //Child Process
	{
		printf("\n");
		int rc;
		if(inputArrayCount>0)
		{
			rc = execlp(full,input,inputArray,NULL);
		}	
		else
		{
			rc = execlp(full,input,NULL);
		}
		perror("SamShell: ERROR : 'execlp() failed\n");

	}
	if(pid>0) //Parent process
	{
		int status;
		int child_pid = wait( &status);
		if(WIFSIGNALED(status))
		{
			printf("\n Abnormal Termination\n");
		}
		else if(WIFEXITED(status))
		{
			int rc = WEXITSTATUS(status);
		}
	}
	
}
void searchInMyPath(char *input,char inputArray[][100],int inputArrayCount)
{	
	int found = false;
	char *inputEnvVariable = getenv("MYPATH");

	if(inputEnvVariable==NULL)
	{
		printf("\nMYPATH environment variable not set. Setting it\n");
		setenv("MYPATH","/bin:.",1);
		inputEnvVariable = getenv("MYPATH");
	}

	char *tokens = strtok(inputEnvVariable,":");
	while(tokens!=NULL)
	{
		DIR * dir = opendir(tokens); // Pointing to the first entry in the directory

		if(dir == NULL)
		{
			perror("SamShell: ERROR : 'opendir()' failed");
			// return EXIT_FAILURE;
		}

		struct dirent * file;

		while((file=readdir(dir))!=NULL)
    	{
    		if(strlen(input) == strlen(file->d_name))
	    	{
	    		// check whether name is a file type and not a directory
	    		if(strncmp(file->d_name,input,strlen(file->d_name))==0)
	    		{
	    			found = true;
	    		}
    		}

		}
		if(found)
		{
			if(strncmp(inputArray[inputArrayCount-1],"&",1)==0)
			{
				executeWithAChildProcessBackground(input,tokens,inputArray,inputArrayCount);
			}
			else
			{
				executeWithAChildProcessForeground(input,tokens,inputArray,inputArrayCount);
			}
			break;
		}
		closedir(dir);
		tokens = strtok(NULL,":");
	}
	if(!found)
	{
		fprintf(stderr,"SamShell: ERROR : '%s' command not found\n",input);
	}
}
char* removeWhiteSpace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace(*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace(*end)) end--;

  // Write new null terminator
  *(end+1) = 0;

  return str;

}

int getArgumentLength(char input[1000])
{
	int count = 0 ; 
	char *tokens = strtok(input," ");
	tokens = strtok(NULL," ");
	while(tokens!=NULL)
	{
		count++;
		tokens = strtok(NULL," ");
	}
	return count;

    
}

void splitCommandAndArgs(char input[1000],int *inputArrayCount,char inputArray[][100])
{
 int i=0;
 // printf("\nInput : %s\n",input);

 char temp2[1000];
 strcpy(temp2,input);
 char *tokens = strtok(temp2," ");
 strcpy(input,temp2);
 // printf("\nTokens1 : %s\n",tokens);
 

 tokens = strtok(NULL," ");
 // printf("\nTokens2 : %s\n",tokens);
 while(tokens!=NULL)
 {	
 	char *inputMe = tokens;
 	strcpy(inputArray[*inputArrayCount],inputMe);
 	*inputArrayCount = *inputArrayCount+1;
 	tokens = strtok(NULL," ");
 }

 // for(i;i<*inputArrayCount;i++)
 // {
 // 	printf("\n%s\n",inputArray[i]);
 // }

 
}

int main()
{

 char input[1000];
 // char history[999][1000]; 
 char history[4][1000]; 
 int historyPointerLocation = 0;
 int noOfElementsInHistory = 0;
 while(1)
 {
 	printf("\nSamShell-v0.0> ");
 	
 	
 	fgets(input,1000,stdin);
 	char* input2 = removeWhiteSpace(input);
 	
 	strcpy(input,input2);
 	char inputArray[2][100];
 	int inputArrayCount = 0,i=0;

 	splitCommandAndArgs(input,&inputArrayCount,inputArray);
 	// strcpy(inputArray[inputArrayCount],NULL);
 	if((strlen(input))==4)
 	{
	 	if(strncmp(input,EXIT,4)==0 || strncmp(input,QUIT,4)==0 )
	 	{
	 		printf("\n");
	 		printf(BYE);
	 		printf("\n");
	 		return EXIT_SUCCESS;
	 	}
	 	if(input[0]=='!')
	 	{
	 		if(isdigit(input[1])&&isdigit(input[2])&&isdigit(input[3]))
	 		{
	 			int hundreds = (input[1] - '0')*100;
	 			int tens = (input[2] - '0')*10;
	 			int ones = (input[3] - '0');
	 			int calculatedNumber = hundreds + tens + ones;
	 			if(calculatedNumber>noOfElementsInHistory || calculatedNumber==0)
	 			{
	 				fprintf(stderr,"SamShell: ERROR : '%s': event not found\n",input);
	 				continue;
	 			}
	 			char* temp = searchHistoryUsingNumber(calculatedNumber,&historyPointerLocation,&noOfElementsInHistory,history);
	 			strcpy(input,temp);
	 			splitCommandAndArgs(input,&inputArrayCount,inputArray);
	 			searchInMyPath(input,inputArray,inputArrayCount);
	 			continue;
	 		}
	 		else
	 		{
	 			
	 				searchInMyPath(input,inputArray,inputArrayCount);
	 				continue;
	 		}
	 	}
 	}	

 	if((strlen(input))==2)
 	{
 		
 		if(input[0]=='!' && input[1]=='!')
 		{
 			if(noOfElementsInHistory!=0)
 			{
 				char* temp;
 				if(historyPointerLocation!=0)
 				{
 					temp = history[historyPointerLocation-1];
 				}
 				else
 				{
 					temp = history[noOfElementsInHistory-1];
 				}
	 			strcpy(input,temp);
	 			splitCommandAndArgs(input,&inputArrayCount,inputArray);
	 			if(strncmp(input,HISTORY,7)==0)
	 			{
	 				printHistory(history,&historyPointerLocation,&noOfElementsInHistory);
	 				continue;
	 			}
	 			searchInMyPath(input,inputArray,inputArrayCount);
	 			continue;
 			}
 			else
 			{
 				fprintf(stderr,"SamShell: ERROR : '%s': event not found\n",input);
 				continue;
 			}
 		}
 	}

 	searchInMyPath(input,inputArray,inputArrayCount);

 	if(historyPointerLocation>3){historyPointerLocation=0;}
 	if(inputArrayCount!=0)
 	{
 		for(i=0;i<inputArrayCount;i++)
 		{
 			strcat(input," ");
 			strcat(input,inputArray[i]);
 		}
 	}
 	strcpy(history[historyPointerLocation],input);
 	// if(historyPointerLocation>998){historyPointerLocation=0;}	
 	historyPointerLocation=historyPointerLocation + 1;
    if(noOfElementsInHistory!=4)
 	{
 		noOfElementsInHistory = noOfElementsInHistory+1;
 	}
 	if(strlen(input)==7)
 	{
	 	if(strncmp(input,HISTORY,7)==0)
	 	{
	 		printHistory(history,&historyPointerLocation,&noOfElementsInHistory);
	 		continue;
	 	}
 	}

 


 	
 }
 return EXIT_SUCCESS;
 
}