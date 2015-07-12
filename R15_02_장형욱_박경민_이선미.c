#include <stdio.h>

int win(int n, int p, int d)
{
	int c=(p+d)%3+1;
	d++;

	return	   ( n>=1 && !( c==1 || win(n-1,1,d) ) )
			|| ( n>=2 && !( c==2 || win(n-2,2,d) ) )
			|| ( n>=3 && !( c==3 || win(n-3,3,d) ) );
}

int main(void)
{
	int n,p,d;
	p=0;
	d=1;

	for(n=0;n<50;n++)
	{
		if(win(n,p,d)==0) printf("win(%2d)= false\n",n);
		else printf("win(%2d)= true\n",n);
	}
 
	return 0;
}