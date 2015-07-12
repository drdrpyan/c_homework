#include <stdio.h>

#define MR	5
#define MC	5

typedef int cel_type;
typedef cel_type mat_type[MR][MC];

void print(mat_type m)
{
	int r,c;

	for(r=0;r<MR;++r) {
		for(c=0;c<MC;++c) {
			printf("%2d",m[r][c]);
		}
		printf("\n");
	}
}

void sym_diag(mat_type m)
{
	int r,c;
	int temp;

	for(r=0;r<MR;++r)
		for(c=0;c<r;++c) {
			temp=m[r][c];
			m[r][c]=m[c][r];
			m[c][r]=temp;
		}
}

void sym_col(mat_type m)
{
	int r,c;
	int temp;

	for(r=0;r<MR;++r)
		for(c=0;c<MC/2;++c) {
			temp=m[r][c];
			m[r][c]=m[r][MC-1-c];
			m[r][MC-1-c]=temp;
		}
}

void sym_row(mat_type m)
{
	int r,c;
	int temp;

	for(r=0;r<MR/2;++r)
		for(c=0;c<MC;++c) {
			temp=m[r][c];
			m[r][c]=m[MR-1-r][c];
			m[MR-1-r][c]=temp;
		}
}

void rot_cw(mat_type m)
{
	sym_diag(m);
	sym_col(m);
}

int main(void)
{
	mat_type a={
		{1,1,1,0,0},
		{2,2,2,1,1},
		{3,3,3,2,2},
		{4,4,4,3,3},
		{5,5,5,4,4}
	};

	print(a); printf("\n");
	sym_diag(a);
	print(a); printf("\n");
	sym_col(a);
	print(a); printf("\n");
	sym_row(a);
	print(a); printf("\n");
	rot_cw(a);
	print(a); printf("\n");
	return 0;
}
