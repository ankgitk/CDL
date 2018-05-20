#include<stdio.h>
#include<stdbool.h>
#include<string.h>

int itable[10][10][10];
char isymbols[10];
int fstates[10];
int fcount;
int m,n;

bool check(char string[],int current_state,int index)
{
	//find index of current_symbol
	printf("Current state %d current symbol -%c-\n",current_state,string[index]);
	int i,j,k;
	for(i=0;i<n;i++)
		if(string[index]==isymbols[i])
			break;
	if(i==n)
		return false;
	if(itable[current_state][i][1]=='-')
	{
		printf("Returning invalid movement\n");
		return false;
	}
	else 
		for(j=1;j<itable[current_state][i][0];j++)
		{
			if(index<strlen(string)-1)
			{
				printf("next state %d\n",itable[current_state][i][j]-48);
				if(check(string,itable[current_state][i][j]-48,index+1)==true)
					return true;
			}
			else
			{
				//check whether current state is final state
				for(k=0;k<fcount;k++)
				{
					if(current_state==fstates[k])
						return true;
				}
				printf("string completed but not reached in final state");
				return false;
			}
		}
	return false;
}

int main()
{

	char c;
	int i,j,k;
	FILE *ptr=fopen("nfa.txt","r");
	k=0;
	while(1)
	{
		fscanf(ptr,"%c",&c);
		if(c==' '){}
		else if(c=='\n')
			break;
		else
			isymbols[k++]=c;
	}
	n=k;
	i=0,j=0,k=1;
	while(fscanf(ptr,"%c",&c)!=EOF)
	{
		if(c==','){}
		else if(c==' ')
		{
			itable[i][j][0]=k;
			k=1;
			j++;
		}
		else if(c=='\n')
		{
			itable[i][j][0]=k;
			k=1;
			j=0;
			i++;
		}
		else
			itable[i][j][k++]=c;
	}
	m=i-1;
	fcount=0;
	for(i=1;i<itable[i][0][0];i++)
		fstates[fcount++]=itable[m][0][i]-48;
	char string[10];
	printf("Enter string : ");
	scanf("%s",string);
	if(check(string,0,0)==true)
		printf("String accepted \n");
	else
		printf("String rejected \n");
		
	return 0;
}
		
