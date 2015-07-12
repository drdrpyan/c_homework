#include <stdio.h>

int win(int apple,int pear)
{
	int result;
	
	result = 0;

	result = result || apple>=3 && !win(apple-3,pear);
	result = result || pear>=3  && !win(apple,pear-3);
	result = result || apple>=1 && pear>=1 && !win(apple-1,pear-1);

	return result;
}

int main(void)
{
	printf("win(7,5)=%s\n", (win(7,5) ? "true" : "false") );
	return 0;
}
