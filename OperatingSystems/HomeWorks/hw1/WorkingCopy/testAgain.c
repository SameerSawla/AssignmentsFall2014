#include<stdio.h>
#include<string.h>

void callMe(char a[6])
{
 int position=-1,i,j;
 for(i=0;i<6;i++)
 {
 	if(a[i]!=' ')
 	{
 		position = i;
 		break;
 	}
 }

 for(i=position,j=0;i<6;i++,j++)
 {
 	a[j] = a[i];

 }
 a[j] = '\0';
 



 printf("%s\n",a);

}

int main()
{	

	char a[6] = " Sam";
	printf("%s\n",a);
	callMe(a);
	printf("%s\n",a);
	return 0;
}