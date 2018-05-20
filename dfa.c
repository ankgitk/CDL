#include<stdio.h>
#include<stdbool.h>
#include<string.h>

int itable[10][10];
int isymbol[10];
int m,n=0;

int getState(int current_state,int current_symbol)
{
	//get symbol number;
	int i;
	for(i=0;i<n;i++)
		if(isymbol[i]==current_symbol)
			break;
	if(i==n)
		return -1;
	if(itable[current_state][i]=='-')
		return -1;
	return itable[current_state][i]-48;
}

int main()
{

	int fstate[10],fcount;
	char string[10];
	char c;
	FILE *ptr=fopen("dfa.txt","r");
	int i,j;
	bool flag=false;
	//read input symbols
	while(!flag)
	{
		fscanf(ptr,"%c",&c);
		switch(c)
		{
			case ' ':
				break;
			case '\n':
				flag=true;
				break;
			default :
				isymbol[n++]=c;
		}
	}
	i=0;j=0;
	while(!feof(ptr))
	{
		fscanf(ptr,"%c",&c);
		switch(c)
		{
			case ' ':
				break;
			case '\n':
				//fcount=j;
				j=0;
				i++;
				break;
			default:
				itable[i][j++]=c;
				fcount=j;
		}
	}
	m=i;
	m-=2;
	j=0;
	//process output symbols;
	for(i=0;i<fcount;i++)
	{
		if(itable[m][i]==',')
		{
		}
		else
		{
			fstate[j++]=itable[m][i]-48;
		}
	}
	fcount=j;
	printf("Enter string : ");
	scanf("%s",string);
	int current_state=0;
	i=0;
	int current_symbol=string[i++];
	flag=false;
	while(1)
	{
		int next_state=getState(current_state,current_symbol);
		printf("Current state %d current symbol %c next state %d\n",current_state,current_symbol,next_state);
		if(next_state<0)
		{
			flag=false;
			break;
		}
		if(i<strlen(string))
		{
			current_state=next_state;
			current_symbol=string[i++];
		}
		else
		{
			current_state=next_state;
			for(j=0;j<fcount;j++)
			{
				if(fstate[j]==current_state)
					flag=true;
			}
			break;
		}
	}
	if(flag)
		printf("String accepted\n");
	else
		printf("String rejected\n");
		
		
	return 0;
}
			
