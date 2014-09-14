#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

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
 		printf("%d\t%s\n",lineNumber,history[*historyPointerLocation]);
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
 		printf("%d\t%s\n",lineNumber,history[i]);
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

void executeWithAChildProcess(char *input)
{
	pid_t pid;
	pid = fork();
	if(pid<0)
	{
		perror("SamShell: ERROR : 'fork() failed");
		return EXIT_FAILURE;
	}

	if(pid==0) //Child Process
	{
		printf("\nIn the child process\n");
	}
}
void searchInMyPath(char *input)
{	
	int found = false;
	char *inputEnvVariable = getenv("MYPATH");
	char *tokens = strtok(inputEnvVariable,":");
	while(tokens!=NULL)
	{
		DIR * dir = opendir(tokens); // Pointing to the first entry in the directory

		if(dir == NULL)
		{
			perror("SamShell: ERROR : 'opendir()' failed");
			// return EXIT_FAILURE;
		}

		printf("\ntokens %s\n",tokens);
		struct dirent * file;

		while((file=readdir(dir))!=NULL)
    	{
    		if(strlen(input) == strlen(file->d_name))
	    	{
	    		if(strncmp(file->d_name,input,strlen(file->d_name))==0)
	    		{
	    			found = true;
	    			printf("found %s in %s\n", file->d_name,tokens);
	    		}
    		}
    		// printf("(d_type is %d)",file->d_type);

		}
		if(found)
		{
			executeWithAChildProcess(input);
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
	 			printf("\n%s\n",input); // Ideally should be directed to execution
	 		}
	 		else
	 		{
	 			searchInMyPath(input);
	 		}
	 	}
 	}	

 	searchInMyPath(input);

 	if(historyPointerLocation>3){historyPointerLocation=0;}
 	strcpy(history[historyPointerLocation],input);
 	// if(historyPointerLocation>998){historyPointerLocation=0;}	
 	historyPointerLocation++;
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