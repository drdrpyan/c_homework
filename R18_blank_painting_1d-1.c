#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BS		6
#define TS		32

typedef int tab_type[TS];
typedef int blk_type[BS];
typedef int bit_type;

#define NUM_INT ((sizeof(bit_type)-1)/sizeof(int)+1)
#define NUM_BIT (sizeof(bit_type)*8)

blk_type blocks[]={
	{1,1,1,0,0,0},
	{1,0,0,0,1,1},
	{1,0,1,0,1,0}
};
int blk_num=sizeof(blocks)/sizeof(blocks[0]);

/********************* time estimation function ********************/
double elapsed_time(int start_flag)
{
	static clock_t start;
	double elap_time;

	switch(start_flag) {
		case 1:
			start=clock();
			elap_time=0.0;
			break;
		case 2:
			elap_time=(double)(clock()-start)/CLOCKS_PER_SEC;
			break;
		case 3:
			elap_time=(double)(clock()-start)/CLOCKS_PER_SEC;
			printf("elapsed time = %.3f\n",elap_time);
			break;
	}
	return elap_time;
}

/*********************** array data structure ***********************/
void set_table(tab_type table,int value)
{
	int i;

	for(i=0;i<TS;++i)
		table[i]=value;
}

void copy_table(tab_type dst,tab_type src)
{
	int i;

	for(i=0;i<TS;++i)
		dst[i]=src[i];
}

int count_table(tab_type table,int value)
{
	int i,cnt=0;

	for(i=0;i<TS;++i)
		if(table[i]==value) cnt++;
	return cnt;
}

void print_table(tab_type table)
{
	int i;

	for(i=0;i<TS;++i) {
		printf("%d",table[i]);
	}
}

int count_block(blk_type block,int value)
{
	int i,cnt=0;

	for(i=0;i<BS;++i)
		if(block[i]==value) cnt++;
	return cnt;
}

void locate(tab_type table,int i0,blk_type block)
{
	int i;

	for(i=0;i<BS;++i)
		if(0<=i0+i && i0+i<TS)
			table[i0+i]=block[i];
}

int make_choices(tab_type choices[])
{

	tab_type choice;
	int i,j;
	int ch_cnt;
	int cnt_blk,cnt_tab;

	ch_cnt=0;
	for(i=0;i<blk_num;++i) {
		cnt_blk=count_block(blocks[i],1);
		for(j=1-BS;j<TS;++j) {
			set_table(choice,0);
			locate(choice,j,blocks[i]);
			cnt_tab=count_table(choice,1);
			if(cnt_tab==cnt_blk)
				copy_table(choices[ch_cnt++],choice);
		}
	}
	return ch_cnt;
}

int is_possible(tab_type tab1,tab_type tab2)
{
	int i;

	for(i=0;i<TS;++i)
		if(tab1[i] && tab2[i]) return 0;
	return 1;
}

void add(tab_type dst,tab_type src)
{
	int i;

	for(i=0;i<TS;++i)
		dst[i]+=src[i];
}

void subtract(tab_type dst,tab_type src)
{
	int i;

	for(i=0;i<TS;++i)
		dst[i]-=src[i];
}

/********************** bitwise data structure **********************/
bit_type tab_to_bit(tab_type tab)
{
	bit_type bt;
	int i;

	bt=0;
	for(i=TS-1;i>=0;--i) {
		bt<<=1;
		bt|=0x00000001 & tab[i];
	}
	return bt;
}

int tables_to_bits(bit_type bts[],tab_type tabs[],int tb_cnt)
{
	int i;

	for(i=0;i<tb_cnt;++i) {
		bts[i]=tab_to_bit(tabs[i]);
	}
	return tb_cnt;
}

/************************** etc function ***************************/
void print_hex(bit_type bt)
{
	int i;
	int num[NUM_INT];

	for(i=0;i<NUM_INT;++i) {
		num[i]=(int)(0xFFFFFFFF & bt);
		bt>>=sizeof(int)*8;
	}
	for(i=NUM_INT-1;i>=0;--i) {
		printf("%08x",num[i]);
	}
}

void print_bit(bit_type bt)
{
	int i;

	for(i=0;i<NUM_BIT;++i) {
		putchar('0'+(int)(1 & bt));
		bt>>=1;
	}
}

void print_node(tab_type table,int result,int depth)
{
	int i;

	for(i=0;i<depth;++i) 
		printf("\t");
	printf("win_table(");
	print_hex(tab_to_bit(table));
	printf(	")=%s\n",(result?"true":"false"));	
}

void print_choices(tab_type choices[],int ch_num)
{
	int i;

	printf("(( full choices #%d))\n",ch_num);
	for(i=0;i<ch_num;++i) {
		printf("cid=%08x: ",tab_to_bit(choices[i]));
		print_table(choices[i]);
		printf("\n");
	}
	printf("\n");
}

void shuffle_choices(tab_type choices[],int ch_num)
{
	int i,rand_i;
	tab_type temp;

	for(i=0;i<ch_num;++i) {
		rand_i=rand()%ch_num;
		copy_table(temp,choices[i]);
		copy_table(choices[i],choices[rand_i]);
		copy_table(choices[rand_i],temp);
	}
}

int win(tab_type table,tab_type choices[],int ch_num)
{
	int result;
	int i;

	result=0;
	for(i=0;i<ch_num;++i) {
		if(is_possible(table,choices[i])) {
			add(table,choices[i]);
			result=result || !win(table,choices,ch_num);
			subtract(table,choices[i]);
		}
	}
	return result;
}

int bin_win(bit_type bt,bit_type bit_cho[],int bc_num)
{
	int result;
	int i;

	result=0;
	for(i=0;i<bc_num;++i) {
		if((bt & bit_cho[i]) == 0) {
			bt ^= bit_cho[i];
			result=result || !bin_win(bt,bit_cho,bc_num);
			bt ^= bit_cho[i];
		}
	}
	return result;
}

int main(void)
{
	tab_type choices[1024];
	bit_type bit_cho[1024];
	int ch_num;
	int bc_num;

	tab_type table;
	bit_type bit_tab;
	int result;

	srand((unsigned)time(NULL));

	ch_num=make_choices(choices);
	shuffle_choices(choices,ch_num);
	bc_num=tables_to_bits(bit_cho,choices,ch_num);
	set_table(table,0);
	bit_tab=tab_to_bit(table);

	print_choices(choices,ch_num);

	elapsed_time(1);
	result=win(table,choices,ch_num);
	elapsed_time(3);
	print_node(table,result,0);
	 
	elapsed_time(1);
	result=bin_win(bit_tab,bit_cho,bc_num);
	elapsed_time(3);
	print_node(table,result,0);

	return 0;
}
