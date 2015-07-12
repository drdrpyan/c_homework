#include <stdio.h>

#define M1 21
#define M2 21

void pyramid1(void)
{
	int i,j, a=1,b;
	char c;
	for(i=0; i!=-1; i+=a)
	{
		for(j=0; j<11-i; j+=1) printf("* ");/*왼쪽*/
		c='.';
		for(j=0 ; j<i; j+=1)
		{
			printf("%c ", c);
			if(j==3)
				c='*';
		}
		/*오른쪽*/
		for(j=0; j<i-1; j+=1)
		{
			if(j<i-5)
				printf("* ");
			else
				printf(". ");
		}
		if(i==0) b=M1-1;
		else b=M1;
		for(j=10+i; j<b; j+=1)
			printf("* ");


		if(i==10)
			a=-1;
		printf("\n");
	}
					
}	

void pyramid2(void)
{
	char c1;
	int a=0,i,j;
	for(i=0; i<M2; i+=1)/*줄*/
	{
		if(i%2==1)/*왼쪽*/
			a+=1;
		for(j=0; j!=a; j+=1)
			printf(". ");
		for(j=0; j<11-a; j+=1)
		{
			if(j==0) c1='*';
			if(j==3) c1='.';
			if(j==6) c1='*';
			if(j==8) c1='.';
			printf("%c ", c1);
		}

		for(j=0; j<10; j+=1)/*오른쪽*/
		{
			if(j<2-a) c1='.';
			if(j==2-a) c1='*';
			if(j==4-a) c1='.';
			if(j==7-a) c1='*';
			if(j>9-a) c1='.';
			printf("%c ", c1);
		}
		printf("\n");
	}
}

int main(void)
{
	pyramid1();
	printf("\n");
	pyramid2();
	return 0;
}