#include <stdio.h>

int main()
{
	int c1,c2=1,a,n=6,s;
	for(s=1; s>-3; s= s-2)
	{
		for(c2=c2; c2!=n; c2=c2+s)
		{
			c1 = 5-c2;
			for(a=1; a<=c1; a=a+1)
			{
				printf(" ");
			}
			for(a=1; a<=c2; a=a+1)
			{
				printf("*");
			}
			printf("\n");
		}
		c2=4;
		n=0;
	}

	return 0;
}
