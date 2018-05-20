#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>

/******  Add space in the end of final states separated by commas  **********/


int itable[20][20][20];
char isymbols[20];
int fstates[20];
int fcount;
int m,n;

struct dfa
{
	int *list;
	bool marked;
}st[20];

int dcount=0;
int dtran[20][20];
void free_memory()
{
	int i;
	for(i=0;i<dcount;i++)
		free(st[i].list);
}
void print_list(int list[])
{
	int i,j;
	printf("{");
	for(i=0;i<=list[0];i++)
	{
		printf("%d,",list[i]);
	}
	printf("}");
}
int indfa(int list[])
{
	int i,j;
	for(i=0;i<dcount;i++)
	{
		bool flag=false;
		if(st[i].list[0]==list[0])
		{
			flag=true;
			for(j=1;j<=list[0];j++)
			{
				if(st[i].list[j]!=list[j])
				{
					flag=false;
					break;
				}
			}
		}
		if(flag)
			return i;
	}
	return -1;
}
			



int getIndex(char ip)
{
	int i;
	for(i=0;i<n;i++)
	{
		if(isymbols[i]==ip)
			return i;
	}
	return -1;
}

bool in(int a,int array[])
{
	int i;
	for(i=1;i<=array[0];i++)
	{
		if(array[i]==a)
			return true;
	}
	return false;
}

int* move(int dstate[],char ip)
{
	int i,j,k,l;
	int *list=(int *)malloc(sizeof(int)*10);
	k=0;
	list[k]=0;
	j=getIndex(ip);
	for(i=1;i<=dstate[0];i++)
	{
		for(l=1;l<=itable[dstate[i]][j][0];l++)
		{
			if(itable[dstate[i]][j][l]!='-')
				if(!in(itable[dstate[i]][j][l],list))
				{
					list[++k]=itable[dstate[i]][j][l];
					list[0]=k;
				}
		}
	}
	//sort output;
	for(i=1;i<=list[0];i++)
		for(j=i+1;j<list[0];j++)
		{
			if(list[i]>list[j])
			{
				int t=list[i];
				list[i]=list[j];
				list[j]=t;
			}
		}
			
	return list;
}
				
int* eclosure(int list[])
{
	int i,j,k,l;
	int *op=(int *)malloc(sizeof(int)*10);
	k=0;
	op[k]=0;
	j=getIndex('e');
	
	//include input set itself to output set
	for(i=1;i<=list[0];i++)
	{
		op[++k]=list[i];
		op[0]=k;
	}
	while(1)
	{
		int kp=k;
		for(i=1;i<=op[0];i++)
		{
			for(l=1;l<=itable[op[i]][j][0];l++)
			{
				if(itable[op[i]][j][l]!='-')
					if(!in(itable[op[i]][j][l],op))
					{
						op[++k]=itable[op[i]][j][l];
						op[0]=k;
					}
			}
		}
		if(kp==k)
			break;
	}
	//sort output;
	for(i=1;i<=op[0]-1;i++)
	{
		for(j=i+1;j<=op[0];j++)
		{
			if(op[i]>op[j])
			{
				int t=op[i];
				op[i]=op[j];
				op[j]=t;
			}
		}
	}
	return op;
}

void convert()
{
	int i,j;
	int arr[]={1,0};
	st[dcount++].list=eclosure(arr);
	st[0].marked=false;
	for(i=0;i<dcount;i++)
	{
		//print_list(st[i].list);
		for(j=0;j<n;j++)
		{
			if(isymbols[j]!='e')
			{
				int *t=eclosure(move(st[i].list,isymbols[j]));
				if(indfa(t)==-1)
				{
					st[dcount++].list=t;
					dtran[i][j]=dcount-1;
				}
				else
				{
					dtran[i][j]=indfa(t);
					free(t);
				}
			}
		}
	}
}
				

int main()
{
	system("COLOR F0");
	char c;
	int i,j,k;
	FILE *ptr=fopen("nfatodfa.txt","r");
	k=0;
	while(1)
	{
		fscanf(ptr,"%c",&c);
		if(c==' '){}
		else if(c=='\n')
			break;
		else
		{
			isymbols[k++]=c;
		}
	}
	n=k;
	i=0,j=0,k=1;
	itable[i][j][k]=0;
	while(fscanf(ptr,"%c",&c)!=EOF)
	{
		//printf("i=%d j=%d k=%d\n",i,j,k);
		if(c==',')
		{
			k++;
			itable[i][j][k]=0;
		}
		else if(c==' ')
		{
			itable[i][j][0]=k;
			k=1;
			j++;
			itable[i][j][k]=0;
		}
		else if(c=='\n')
		{
			itable[i][j][0]=k;
			k=1;
			j=0;
			i++;
			itable[i][j][k]=0;
		}
		else if(c=='-')
			itable[i][j][k]=c;
		else
			itable[i][j][k]=(itable[i][j][k])*10+(c-48);
		//printf("itable[%d][%d][%d]=%d\n",i,j,k,itable[i][j][k]);
			
	}
	fclose(ptr);
	m=i;
	fcount=0;
	for(i=1;i<=itable[m][0][0];i++)
		fstates[fcount++]=itable[m][0][i];
	printf("Input symbols\n",n,fcount);
	for(i=0;i<n;i++)
		printf("%c ",isymbols[i]);
	printf("\nTransition table\n");
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			for(k=1;k<=itable[i][j][0];k++)
			{
				printf(".%d.",itable[i][j][k]);
			}
			printf("|");
		}
		printf("\n");
	}
	printf("Final states\n");
	for(i=0;i<fcount;i++)
		printf("%d ",fstates[i]);
	printf("\n");
	convert();
	free_memory();
	printf("DFA\n");
	for(i=0;i<dcount;i++)
	{
		for(j=0;j<n;j++)
		{
			if(isymbols[j]!='e')
			{
				printf("%d ",dtran[i][j]);
			}
		}
		printf("\n");
	}
	return 0;
}
