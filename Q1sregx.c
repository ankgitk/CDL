#include<stdio.h>
#include<string.h>

int main()
{
	system("COLOR F0");
	FILE *fp=fopen("regex.txt","r");
	char regex[100];
	fscanf(fp,"%s",regex);
	char string[100];
	int m,n,i,j=0,k=0;
	char components[10][10];
	for(i=0;i<strlen(regex);i++)
	{
		if(regex[i]=='(')
		{/*ignore*/}
		else if(regex[i]=='+')
		{
			components[j][k]=0;
			j++;
			k=0;
		}
		else if(regex[i]==')')
		{
			components[j][k]=0;
			break;
		}
		else
		{
			components[j][k++]=regex[i];
		}
	}
	m=j+1;
	printf("Components are \n");
	for(i=0;i<m;i++)
		printf("-%s- ",components[i]);
	printf("\n");
	printf("Enter the string:\n");
	scanf("%s",string);
	//check string
	if(regex[strlen(regex)-1]!='*')
	{
		for(i=0;i<m;i++)
		{
			if(strcmp(components[i],string)==0)
			{
				printf("String accepted\n");
				return 0;
			}
		}
		printf("String rejected\n");
		return 0;
	}
			
	for(i=0;i<strlen(string);)
	{
		int p=i;
		for(j=0;j<m;j++)
		{
			printf("i=%d j=%d\n",i,j);
			if(string[i]==components[j][0])
			{
				int t=i;
				for(k=0;k<strlen(components[j]);k++)
				{
					printf("k=%d \n",k);
					if(components[j][k]==string[t])
						t++;
					else
						break;
				}
				printf("-t=%d i=%d length=%d-",t,i,strlen(components[j]));
				if(t==strlen(components[j])+i)
					i=t;
			}
		}
		if(p==i)
		{
			printf("String rejected\n");
			return 0;
		}
	}	
	printf("String accepted\n");
	return 0;
}
