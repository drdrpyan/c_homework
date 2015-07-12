#include <stdio.h>

void print(int m[2][3])
{
	int r,c;

	for(r=0;r<2;++r) {
		for(c=0;c<3;++c)
			printf("%d ",m[r][c]);
		printf("\n");
	}
}

int equal(int m1[2][3],int m2[2][3])
{
	int r,c;
	return 1;
}

void swap(int m1[2][3],int m2[2][3])
{
	int temp;
	int r,c;
}

void add(int dst[2][3],int src[2][3])
{
	int r,c;
}

void subtract(int dst[2][3],int src[2][3])
{
	int r,c;
}

void set(int m[2][3],int value)
{
	int r,c;
}

void copy(int dst[2][3],int src[2][3])
{
	int r,c;
}

int main(void)
{
	int a[2][3]={ {1,2,3}, {4,5,6} };
	int b[2][3]={ {1,1,1}, {2,2,2} };

	print(a);	printf("\n");
	print(b);	printf("\n");

	if(equal(a,b)) printf("equal\n");
	else printf("not equal\n");

	swap(a,b);
	print(a);	printf("\n");
	print(b);	printf("\n");

	add(a,b);
	print(a);	printf("\n");
	print(b);	printf("\n");

	subtract(a,b);
	print(a);	printf("\n");
	print(b);	printf("\n");

	set(a,3);
	print(a);	printf("\n");

	copy(a,b);
	print(a);	printf("\n");
	print(b);	printf("\n");

	return 0;
}
