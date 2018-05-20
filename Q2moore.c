#include<stdio.h>
#include<stdbool.h>
#include<string.h>

int m,n,itable[10][10];

int getState(int current_state,int current_symbol)
{
	if(current_symbol-48<n)
	{
		if(itable[current_state][current_symbol-48]=='-')
			return -1;
		else
			return itable[current_state][current_symbol-48]-48;
		
	}
	else
	{
		return -1;
	}
}

int main()
{
	system("COLOR F0");
	char osymbol[10];
	int i=0,j=0;
	FILE *ptr=fopen("moore.txt","r");
	char c,string[10];;
	while(!feof(ptr))
	{
		fscanf(ptr,"%c",&c);
		switch(c)
		{
			case ' ':
				j++;
				n=j;
				break;
			case '\n':
				i++;
				j=0;
				break;
			default:
				itable[i][j]=c;
		}
	}
	m=i+1;
	for(i=0;i<m;i++)
	{
		osymbol[i]=itable[i][n];
	}
	printf("Enter string : ");
	scanf("%s",string);
	i=0;
	j=0;
	char output[10];
	int current_state=0;
	int current_symbol=string[i++];
	output[j++]=osymbol[current_state];
	bool flag=false;
	printf("current_state %d,output %c\n",current_state,osymbol[current_state]);
	while(1)
	{
		int next_state=getState(current_state,current_symbol);
		printf("current_state %d,current_symbol %c,next_state %d,output %c\n",current_state,current_symbol,next_state,osymbol[next_state]);
		if(next_state<0)
		{
			flag=false;
			break;
		}
		current_state=next_state;
		output[j++]=osymbol[current_state];
		if(i<strlen(string))
		{
			current_symbol=string[i++];
		}
		else
		{
			flag=true;
			break;
		}
	}
	if(flag)
		printf("Output %s\n",output);
	else
		printf("Invalid input\n");
	
	return 0;
}
	
