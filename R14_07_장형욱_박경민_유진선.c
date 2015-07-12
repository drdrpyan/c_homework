#include <stdio.h>

#define BR	2
#define BC	2

#define MR	4
#define MC	4

typedef int blk_type[BR][BC];
typedef int mat_type[MR][MC];

void print_blk(blk_type bk)/*블록 출력*/
{
	int r,c;

	for(r=0;r<BR;++r) {
		for(c=0;c<BC;++c)
			if(bk[r][c]) printf(" #");
			else printf(" .");
		printf("\n");
	}
}

void print_mat(mat_type mt)/*매트릭스 출력*/
{
	int r,c;

	for(r=0;r<MR;++r) {
		for(c=0;c<MC;++c)
			if(mt[r][c]) printf(" #");
			else printf(" .");
		printf("\n");
	}
}

int valid_mat(int mr,int mc)/*for 문 안에 조건문으로 valid_mat를 넣음  0<=mr<MR, 0<=mc<MC*/
{
	return 0<=mr && mr<MR && 0<=mc && mc<MC;
}

void set_mat(mat_type mt,int val)/*매트릭스를 0으로 초기화 시킬 때 사용*/
{
	int r,c;

	for(r=0;r<MR;++r)
		for(c=0;c<MC;++c)
			mt[r][c]=val;
}

void copy(mat_type mt,blk_type bk,int r0,int c0)/*r0,c0 은 블록의 (0,0)이 위치하는 매트릭스 위의 위치)*/
{
	int r,c;

	/* 적당한 코드를 여기에 채워라 */
	for(r=0;r<BR;r++)
		for(c=0;c<BC;c++)
		{			
			if(bk[r][c]&&valid_mat(r0+r, c0+c)){
				mt[r0+r][c0+c]=bk[r][c];
			}
		}

}

int count_mat(mat_type mt,int val)
{
	int r,c;
	int cnt;

	/* 적당한 코드를 여기에 채워라 */

	cnt=0;
	for(r=0;r<MR;r++)
		for(c=0;c<MC;c++)
			if(mt[r][c]==val)
				cnt+=1;			
	return cnt;
}

int count_blk(blk_type bk,int val)
{
	int r,c;
	int cnt;

	/* 적당한 코드를 여기에 채워라 */

	cnt=0;
	for(r=0;r<BR;r++)
		for(c=0;c<BC;c++)
			if(bk[r][c]==val)
				cnt+=1;
	return cnt;
}

void print_possible(blk_type bk)
{
	mat_type mt;
	int r,c;

	/* 적당한 코드를 여기에 채워라 */

	for(r=-1;r<MR;r++)
		for(c=-1;c<MC;c++)
		{
			copy(mt,bk,r,c);
			if(count_mat(mt,1)==count_blk(bk,1)){
				print_mat(mt);
				printf("\n");
			}
			set_mat(mt, 0);
		}
}

int main(void)
{
	blk_type bk1={ {1,0},{1,0} };
	blk_type bk2={ {1,0},{0,0} };
	blk_type bk3={ {1,0},{0,1} };

	printf("==< bk1 >==\n");
	print_blk(bk1); 
	printf("\n");
	print_possible(bk1);

	printf("==< bk2 >==\n");
	print_blk(bk2); 
	printf("\n");
	print_possible(bk2);

	printf("==< bk3 >==\n");
	print_blk(bk3); 
	printf("\n");
	print_possible(bk3);
	return 0;
}