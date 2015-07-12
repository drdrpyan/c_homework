#include <stdio.h>
#include <math.h>

int pyramid(int x, int y)
{
	return
	(y>=2*abs(x-10) && y-5<=2*abs(x-10)) ||
	(y-10>=2*abs(x-10) && y-15<=2*abs(x-10));
}

int main()
{
	int x,y;
	for(y=20; y>=0; y-=1)
	{
		for(x=0; x<21; x+=1)
			if(pyramid(x,y)) printf("* ");
			else printf(". ");
		printf("\n");
	}
	return 0;
}