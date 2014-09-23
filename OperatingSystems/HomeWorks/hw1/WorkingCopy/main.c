#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

#define BYE "Bye"
#define HISTORY "history"
#define EXIT "exit"
#define QUIT "quit"
#define true 1
#define false 0

int searchForPiping(char inputArray[][100],int *inputArrayCount)
{
	int i=0;
	for(i;i<*inputArrayCount;i++)
	{	
		if(strncmp(inputArray[i],"|",1)==0)
		{
			return 1;
		}
	}
 	return false; 
}


int searchForRedirection(char inputArray[][100],int *inputArrayCount)
{
	int i=0;
	for(i;i<*inputArrayCount;i++)
	{
		if(strncmp(inputArray[i],"<",1)==0)
		{
			return 1;
		}
		if(strncmp(inputArray[i],">>",2)==0)
		{	
			return 3;
		}
		if(strncmp(inputArray[i],">",1)==0)
		{
			return 2;
		}
		
	}
 	return false; 
}
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
	}
	if(pid==0) //Child Process
	{
		sleep(2);
		printf("\n");
		if(inputArrayCount>0)
		{
			execlp(full,input,inputArray,NULL);
		}	
		else
		{
			execlp(full,input,NULL);
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
	}
	if(pid==0) //Child Process
	{
		printf("\n");
		if(inputArrayCount>0)
		{
			execlp(full,input,inputArray,NULL);
		}	
		else
		{
			execlp(full,input,NULL);
		}
		perror("SamShell: ERROR : 'execlp() failed\n");

	}
	if(pid>0) //Parent process
	{
		//Something to be done.
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

 char temp2[1000];
 strcpy(temp2,input);
 char *tokens = strtok(temp2," ");
 strcpy(input,temp2);

 tokens = strtok(NULL," ");
 while(tokens!=NULL)
 {	
 	char *inputMe = tokens;
 	strcpy(inputArray[*inputArrayCount],inputMe);
 	*inputArrayCount = *inputArrayCount+1;
 	tokens = strtok(NULL," ");
 }

 
}

char * searchThePathForInput(char input[100])
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
			closedir(dir);
			return tokens;
		}
		closedir(dir);
		tokens = strtok(NULL,":");
	}
	if(!found)
	{
		fprintf(stderr,"SamShell: ERROR : '%s' command not found\n",input);
		return "null";
	}
	return "null";
}

void executeRightOneRedirectionForeGround(char *full,char* input,char *half2,char firstHalfArray[][100], int firstHalfArrayCt)
{
	char* fileName = removeWhiteSpace(half2);
 	int copyFD = dup(1);
 	
    close(1);
    open(fileName, O_WRONLY | O_CREAT | O_TRUNC,0660);

	pid_t pid;
	pid = fork();
	
	if(pid<0)
	{
		perror("SamShell: ERROR : 'fork() failed");
	}
	if(pid==0) //Child Process
	{		
		if(firstHalfArrayCt>0)
		{
			execlp(full,input,firstHalfArray,NULL);
		}
		else
		{
			execlp(full,input,NULL);
		}
		perror("SamShell: ERROR : 'execlp() failed\n");

	}
	if(pid>0) //Parent process
	{
			wait(NULL);
			dup2(copyFD,1);
	}
}

void executeLeftRedirectionForeGround(char *full,char* input,char *half2,char firstHalfArray[][100], int firstHalfArrayCt)
{
	char* fileName = removeWhiteSpace(half2);
 	int copyFD = dup(0);
 	// close(0);
	int fd = open(fileName, O_RDONLY | O_CREAT ,0660);
	dup2(fd,0);
	close(fd);

 	pid_t pid;
	pid = fork();
	
	if(pid<0)
	{
		perror("SamShell: ERROR : 'fork() failed");
	}
	if(pid==0) //Child Process
	{		
		if(firstHalfArrayCt>0)
		{
			execlp(full,input,firstHalfArray,NULL);	
		}
		else
		{
			execlp(full,input,NULL);	
		}
	}
	if(pid>0) //Parent process
	{
			wait(NULL);
			dup2(copyFD,0);
	}
}


void executeRightTwoRedirectionForeGround(char *full,char* input,char *half2,char firstHalfArray[][100], int firstHalfArrayCt)
{
	char* fileName = removeWhiteSpace(half2);
 	int copyFD = dup(1);
 	
    close(1);
    open(fileName, O_WRONLY | O_CREAT | O_APPEND,0660);

	pid_t pid;
	pid = fork();
	
	if(pid<0)
	{
		perror("SamShell: ERROR : 'fork() failed");
	}
	if(pid==0) //Child Process
	{		
		if(firstHalfArrayCt>0)
		{
			execlp(full,input,firstHalfArray,NULL);
		}
		else
		{
			execlp(full,input,NULL);
		}
		perror("SamShell: ERROR : 'execlp() failed\n");

	}
	if(pid>0) //Parent process
	{
			wait(NULL);
			dup2(copyFD,1);
	}
}

void redirectionExecution(char *input,char inputArray[][100],int *inputArrayCount,int *redirectQ)
{

 char operator[2];	
 int firstHalfArrayCt = 0;
 char half2[100];
 int i=0;
 int cmpCount=1;

 if(*redirectQ == 1)
 {
 	strcpy(operator,"<");
 }
 if(*redirectQ == 2)
 {
 	strcpy(operator,">");
 }
 if(*redirectQ == 3)
 {
 	cmpCount = 2;
 	strcpy(operator,">>");
 }

 for(i;i<*inputArrayCount;i++)
 {
 	if(strncmp(inputArray[i],operator,cmpCount)==0)
 	{
 		break;
 	}
 	firstHalfArrayCt++;
 }
 
 char firstHalfArray[firstHalfArrayCt][100];

 strcpy(half2,"");
 for(i=0;i<*inputArrayCount;i++)
 {
 	if(strncmp(inputArray[i],operator,cmpCount)==0)
 	{
 		i++;
 		break;
 	}
 	strcpy(firstHalfArray[i],inputArray[i]);
 }
 
 for(i;i<*inputArrayCount;i++)
 {
 	strcat(half2,inputArray[i]);
 }
 
 char *tokens = searchThePathForInput(input);
 if(strncmp(tokens,"null",4)!=0)
 {
    int n = strlen(input) + strlen(tokens);
	char full[n];
	strcpy(full,tokens);
	strcat(full,"/");
	strcat(full,input);

	if(cmpCount==2)
	{
		executeRightTwoRedirectionForeGround(full,input,half2,firstHalfArray,firstHalfArrayCt);
	}
	else if(cmpCount==1)
		  {
		  	if(strncmp(operator,">",1)==0)
		  	{
    			executeRightOneRedirectionForeGround(full,input,half2,firstHalfArray,firstHalfArrayCt);
		  	}
		  	if(strncmp(operator,"<",1)==0)
		  	{
    			executeLeftRedirectionForeGround(full,input,half2,firstHalfArray,firstHalfArrayCt);
            }
 		  }
 }
}
void pipeImplementation(char *input,char argsOne[][100], int *argsOneCount, char *token1, char *input2, char argsTwo[][100],int *argsTwoCount,char *token2)
{
 	int p[2],status;
	pid_t child1;
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
			if(*argsOneCount>0)
			{
				execlp(token1,input,argsOne,NULL);
			}
			else
			{
				execlp(token1,input,NULL);
			}
		}
		else
		{
			pid_t a = wait(&status);
			dup2(p[0],0);
			close(p[0]);
			close(p[1]);
			if(*argsTwoCount>0)
			{
				execlp(token2,input2,argsTwo,NULL);
			}
			else
			{
				execlp(token2,input2,NULL);
			}
		}
		
	}
	else
	{
		wait(NULL);
	}

	waitpid(child1, &status, WUNTRACED);
}

void pipingExecution(char *input,char inputArray[][100],int *inputArrayCount)
{
 char input2[1000],token1[1000],token2[1000];
 int argsOneCount = 0,argsTwoCount = *inputArrayCount-1,i=0, j=0;;
 for(i;i<*inputArrayCount;i++)
 {
 	if(strncmp(inputArray[i],"|",1)==0)
 	{
 		break;
 	}
 	argsOneCount++;
 	argsTwoCount--;
 }

 char oneArgs[argsOneCount][100], twoArgs[argsTwoCount][100];

 for(i=0;i<argsOneCount;i++)
 {
 	if(strncmp(inputArray[i],"|",1)==0)
 	{
 		break;
 	}
 	strcpy(oneArgs[i],inputArray[i]);
 }
 i++;
 for(i,j;j<argsTwoCount;i++,j++)
 {
 	strcpy(twoArgs[j],inputArray[i]);
 }
 char *token;
 token = searchThePathForInput(input);
 strcpy(token1,token);
 token = searchThePathForInput(twoArgs[0]); 
 strcpy(token2,token);

 strcpy(input2,twoArgs[0]);
 char argsTwoFinal[argsTwoCount-1][100];
 for(i=1,j=0;i<argsTwoCount;i++,j++)
 {
  strcpy(argsTwoFinal[j],twoArgs[i]);
 }
 argsTwoCount = argsTwoCount - 1;

 if(strncmp(token1,"null",4)!=0 && strncmp(token2,"null",4)!=0)
 {
 	strcat(token1,"/");
 	strcat(token1,input);

 	strcat(token2,"/");
 	strcat(token2,input2);
 	pipeImplementation(input,oneArgs,&argsOneCount,token1,input2,argsTwoFinal,&argsTwoCount,token2);
 }
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
 	// strcpy(inputArray[inputArrayCount],NULL); // can be replaced by "" ?
 	int redirectQ = searchForRedirection(inputArray,&inputArrayCount);
 	if(redirectQ!=0)
 	{
 		printf("\ninput %s\n",input);
 		redirectionExecution(input, inputArray,&inputArrayCount,&redirectQ);
 		printf("\ninput %s\n",input);
 		continue;
 	}

 	int pipeQ = searchForPiping(inputArray,&inputArrayCount);
 	if(pipeQ==1)
 	{
 		pipingExecution(input,inputArray,&inputArrayCount);
 		int i=0;
 		for(i;i<inputArrayCount;i++)
 		{
 			strcat(input," ");
 			strcat(input,inputArray[i]);
 		}
 		printf("\nhist %s\n",history[historyPointerLocation-1]);
 		printf("\nhist2 %s\n",history[historyPointerLocation]);
 		strcpy(history[historyPointerLocation],input);
 		printf("\nhist3 %s\n",history[historyPointerLocation]);
 		continue;
 	}
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