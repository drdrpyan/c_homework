#include <stdio.h>

#define BR				4
#define BC				4
#define MR				7
#define MC				7

typedef int cel_type;
typedef cel_type blk_type[BR][BC];
typedef cel_type mat_type[MR][MC];

cel_type blocks[][BR][BC] = {
	{
		{1,0,0,0},
		{1,0,0,0},
		{1,0,0,0},
		{1,0,0,0}
	},
	{
		{1,1,0,0},
		{1,1,0,0},
		{0,0,0,0},
		{0,0,0,0}
	},
	{
		{1,1,1,0},
		{0,1,0,0},
		{0,0,0,0},
		{0,0,0,0}
	},
	{
		{1,0,0,0},
		{1,1,0,0},
		{0,1,0,0},
		{0,0,0,0}
	},
	{
		{1,1,0,0},
		{0,1,1,0},
		{0,0,0,0},
		{0,0,0,0}
	},
	{
		{1,0,0,0},
		{1,0,0,0},
		{1,1,0,0},
		{0,0,0,0}
	},
	{
		{1,1,1,0},
		{0,0,1,0},
		{0,0,0,0},
		{0,0,0,0}
	}
};
int num_blocks=sizeof(blocks)/sizeof(blocks[0]);


void copy_block(blk_type dst,blk_type src)
{
	int r,c;
	for(r=0; r<BR; ++r)
		for(c=0; c<BC; ++c)
			dst[r][c] = src[r][c];
}

int count_blk(blk_type bk,cel_type v)
{
	int r,c;
	int cnt=0;
	for(r=0; r<BR; ++r)
		for(c=0; c<BC; ++c)
			if(bk[r][c] == v) cnt++;
	return cnt;
}

void rotate_cw(blk_type bk)
{
	int r,c;
	cel_type temp;

	for(r=0;r<(BR/2);r++)
	{
		for(c=0;c<BC;c++){
			temp=bk[r][c];
			bk[r][c]=bk[BR-1-r][c];
			bk[BR-1-r][c]=temp;
		}
	}
	for(r=0;r<BR;r++)
	{
		for(c=0;c<r;c++){
			temp=bk[r][c];
			bk[r][c]=bk[c][r];
			bk[c][r]=temp;
		}
	}
}

void set_matrix(mat_type m,cel_type value)
{
	int r,c;
	for(r=0; r<MR; ++r)
		for(c=0; c<MC; ++c)
			m[r][c] = value;
}

void copy_matrix(mat_type dst,mat_type src)
{
	int r,c;
	for(r=0; r<MR; ++r)
		for(c=0; c<MC; ++c)
			dst[r][c] = src[r][c];
}

int count_mat(mat_type mt,cel_type v)
{
	int r,c;
	int cnt=0;
	for(r=0; r<MR; ++r)
		for(c=0; c<MC; ++c)
			if(mt[r][c] == v) cnt++;
	return cnt;
}

int valid_mat_index(int r,int c)
{
	return 0<=r && r<MR && 0<=c && c<MC;
}

void swap_matrix(mat_type m1,mat_type m2)
{
	cel_type temp;
	int r,c;
	for(r=0; r<MR; ++r)
		for(c=0; c<MC; ++c){
			temp = m1[r][c];
			m1[r][c] = m2[r][c];
			m2[r][c] = temp;
		}
}

int equal_matrix(mat_type m1,mat_type m2)
{
	int r,c;
	for(r=0; r<MR; ++r)
		for(c=0; c<MC; ++c)
			if(m1[r][c] != m2[r][c]) return 0;
	return 1;
}

void print_matrix(mat_type m)
{
	int r,c;

	printf("   ");
	for(c=0;c<MC;++c)
		printf("%2d",c);
	printf("\n");

	for(r=0;r<MR;++r) {
		printf("%2d: ",r);
		for(c=0;c<MC;++c) {
			if(m[r][c]!=0) 
				printf("# ");
			else 
				printf(". ");
		}
		printf("\n");
	}
}

int erase_matrix(mat_type ml[],int ml_cnt,int inx) // inx위치의 matrix를 제거하고 해당 위치로 제일 마지막 matrix를 가져옴
{
	swap_matrix(ml[inx], ml[--ml_cnt]);
	return ml_cnt;
}

int find_matrix(mat_type ml[],int ml_cnt, mat_type m) // matrix list내에서 m과 같은것의 위치를 return, 없으면 가장 마지막을 return
{
	int i;
	for(i=0;i<ml_cnt;++i) {
		if(equal_matrix(ml[i], m)) {
			return i;
		}
	}
	return i;
}

int erase_duplication(mat_type ml[],int ml_cnt) // matrixt list내에서 중복된 matrix들 제거, 제거한 후 list 개수를 return
{
	int i;

	for(i=0; i<ml_cnt; ++i)
	{
		while(find_matrix(ml+1+i, ml_cnt-1-i, ml[i])+1+i != ml_cnt)
			ml_cnt=erase_matrix(ml,ml_cnt,i);
	}
	return i;
}

void locate(mat_type ch,int r0,int c0, blk_type bk){
	int br,bc;
	for(br=0;br<BR;br++)
		for(bc=0;bc<BC;bc++){			
			if(bk[br][bc]&&valid_mat_index(r0+br, c0+bc))
				ch[r0+br][c0+bc]=bk[br][bc];
		}
}

int possible_locations(mat_type fc[],blk_type bk) // 7*7행렬 내에 해당 block이 몇개 들어가는지 return
{
	mat_type ch;
	int r,c;
	int ps_cnt;
	
	for(ps_cnt=0; count_mat(fc[ps_cnt], 1)!=0 ;ps_cnt++);
	for(r=-3;r<MR+3;r++)
		for(c=-3;c<MC+3;c++){
			set_matrix(ch, 0);
			locate(ch, r, c, bk);
			if(count_mat(ch, 1) == count_blk(bk, 1)){				
				copy_matrix(fc[ps_cnt++], ch);
			}
		}
	return ps_cnt;
}

int make_full_choices(mat_type fc[])
{
	blk_type bk;
	int i,rotate_id;
	int fc_cnt;

	for(i=0; i<num_blocks; ++i){
		copy_block(bk, blocks[i]);
		for(rotate_id=0; rotate_id<4; ++rotate_id){
			fc_cnt = possible_locations(fc, bk);
			rotate_cw(bk);
		}
		fc_cnt=erase_duplication(fc,fc_cnt);
	}	
	return fc_cnt;
}

int main(void)
{
	mat_type fc_list[1024];
	int fc_cnt;
	int fc_id;

	fc_cnt=make_full_choices(fc_list);
	for(fc_id=0;fc_id<fc_cnt;++fc_id) {
		printf("choice id=%d\n",fc_id);
		print_matrix(fc_list[fc_id]);
		printf("\n");
	}
	return 0;
}
