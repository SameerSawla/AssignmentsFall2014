#include<stdio.h>
#include<string.h>

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

void splitCommandAndArgs(char input[1000])
{
 char temp[1000] ;
 strcpy(temp,input);
 int n = getArgumentLength(temp);	
 char inputArray[n][100];
 int inputArrayCount=0,i=0;
 printf("\nInput : %s\n",input);

 char *tokens = strtok(input," ");
 printf("\nTokens1 : %s\n",tokens);


 tokens = strtok(NULL," ");
 printf("\nTokens2 : %s\n",tokens);
 while(tokens!=NULL)
 {	
 	char *inputMe = tokens;
 	strcpy(inputArray[i],inputMe);
 	inputArrayCount++;
 	tokens = strtok(NULL," ");
 }

 for(i;i<inputArrayCount;i++)
 {
 	printf("\n%s\n",inputArray[i]);
 }


}


int main()
{
	char input[1000]="ls -l";
	// strcpy(input,userInput);
	splitCommandAndArgs(input);
	return 0;
}