#include <stdio.h>

#define MR		7
#define MC		7
#define NUM	(MR*MC)

typedef int cel_type;
typedef cel_type mat_type[MR][MC];

#define CEL_SIZE	sizeof(cel_type)

int save_matrix_txt(char* file_name,mat_type m)
{
	FILE* fp;
	int r,c;

	/* 여기에 적절한 코드를 채워라. */
	return 0;
}

int load_matrix_txt(char* file_name,mat_type m)
{
	FILE* fp;
	int r,c;

	/* 여기에 적절한 코드를 채워라. */
	return 0;
}

int save_matrix_bin(char* file_name,mat_type m)
{
	FILE* fp;

	/* 여기에 적절한 코드를 채워라. */
	return 0;
}

int load_matrix_bin(char* file_name,mat_type m)
{
	FILE* fp;

	/* 여기에 적절한 코드를 채워라. */
	return 0;
}

void print_matrix(mat_type m)
{
	int r,c;

	for(r=0;r<MR;++r) {
		for(c=0;c<MC;++c)
			fprintf(stdout,"%2d ",m[r][c]);
		fprintf(stdout,"\n");
	}
}

int main(void)
{
	mat_type m={
		{11,12,13,14,15,16,17},
		{21,22,23,24,25,26,27},
		{31,32,33,34,35,36,37},
		{41,42,43,44,45,46,47},
		{51,52,53,54,55,56,57},
		{61,62,63,64,65,66,67},
		{71,72,73,74,75,76,77}
	};

	print_matrix(m);
	printf("\n");

	if(save_matrix_txt("matrix.txt",m)<0) 
		return -1;

	if(load_matrix_txt("matrix.txt",m)<0)
		return -1;

	print_matrix(m);
	printf("\n");

	if(save_matrix_bin("matrix.bin",m)<0)
		return -1;

	if(load_matrix_bin("matrix.bin",m)<0)
		return -1;

	print_matrix(m);
	printf("\n");

	return 0;
}