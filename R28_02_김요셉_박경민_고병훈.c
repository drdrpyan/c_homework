#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


#define MR				7
#define MC				9
#define BR				4
#define BC				4

#define CMD_BACK		-1
#define CMD_QUIT		-2

typedef int cel_type;
typedef cel_type mat_type[MR][MC];
typedef cel_type blk_type[BR][BC];

typedef unsigned long long bin_type;

void copy_block(blk_type dst,blk_type src)
{
	int r,c;

	for(r=0;r<BR;++r)
		for(c=0;c<BC;++c)
			dst[r][c]=src[r][c];
}

int count_blk(blk_type bk,cel_type v)
{
	int r,c;
	int cnt=0;

	for(r=0;r<BR;++r)
		for(c=0;c<BC;++c)
			if(bk[r][c]==v) cnt++;
	return cnt;
}

void rotate_cw(blk_type bk)
{
	int r,c;
	cel_type temp;

	for(r=0;r<BR;++r)
		for(c=0;c<r;++c) {
			temp=bk[c][r];
			bk[c][r]=bk[r][c];
			bk[r][c]=temp;
		}
	for(r=0;r<BR;++r)
		for(c=0;c<BC/2;++c) {
			temp=bk[r][BC-1-c];
			bk[r][BC-1-c]=bk[r][c];
			bk[r][c]=temp;
		}
}

void set_matrix(mat_type m,cel_type value)
{
	int r,c;

	for(r=0;r<MR;++r) 
		for(c=0;c<MC;++c)
			m[r][c]=value;
}

void copy_matrix(mat_type m_dst,mat_type m_src)
{
	int r,c;

	for(r=0;r<MR;++r)
		for(c=0;c<MC;++c)
			m_dst[r][c]=m_src[r][c];
}

int count_mat(mat_type mt,cel_type v)
{
	int r,c;
	int cnt=0;

	for(r=0;r<MR;++r)
		for(c=0;c<MC;++c)
			if(mt[r][c]==v) cnt++;
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

	for(r=0;r<MR;++r)
		for(c=0;c<MC;++c) {
			temp=m1[r][c];
			m1[r][c]=m2[r][c];
			m2[r][c]=temp;
		}
}

int equal_matrix(mat_type m1,mat_type m2)
{
	int r,c;

	for(r=0;r<MR;++r) 
		for(c=0;c<MC;++c)
			if(m1[r][c]!=0 && m2[r][c]==0 || 
				m1[r][c]==0 && m2[r][c]!=0)
				return 0;
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

void print_matrix_2(mat_type m1,mat_type m2)
{
	int r,c;

	printf("   ");
	for(c=0;c<MC;++c)
		printf("%2d",c);
	printf("\t   ");
	for(c=0;c<MC;++c)
		printf("%2d",c);
	printf("\n");

	for(r=0;r<MR;++r) {
		printf("%2d: ",r);
		for(c=0;c<MC;++c) {
			if(m1[r][c]!=0) 
				printf("# ");
			else 
				printf(". ");
		}
		printf("\t");
		printf("%2d: ",r);
		for(c=0;c<MC;++c) {
			if(m2[r][c]!=0) 
				printf("# ");
			else 
				printf(". ");
		}
		printf("\n");
	}
}


int erase_matrix(mat_type ml[],int ml_num,int inx)
{
	swap_matrix(ml[inx],ml[--ml_num]);
	return ml_num;
}

int find_matrix(mat_type ml[],int ml_num,mat_type m)
{
	int i;

	for(i=0;i<ml_num;++i) {
		if(equal_matrix(ml[i],m)) 
			return i;
	}
	return i;
}
int make_fullnum(mat_type ml[], int ml_num,int inx)
{
	int i;
	for(i=inx;i<ml_num-1;++i)
		swap_matrix(ml[i],ml[i+1]);
	ml_num--;
	return ml_num;
}
int erase_duplication(mat_type ml[],int ml_num)
{
	int i,ml_id;

	for(i=0;i<ml_num;++i) {
		while((ml_id=find_matrix(ml+i+1,ml_num-i-1,ml[i]))<ml_num-i-1) {
			make_fullnum(ml+i+1,ml_num-i-1,ml_id);
			--ml_num;
		}
	}
	return i;
}

void locate(mat_type ch,int r0,int c0,blk_type bk)
{
	int br,bc;

	for(br=0;br<BR;++br)
		for(bc=0;bc<BC;++bc)
			if(valid_mat_index(r0+br,c0+bc))
				ch[r0+br][c0+bc]=bk[br][bc];
}

int possible_locations(mat_type fc[],blk_type bk)
{
	mat_type ch;
	int r,c;
	int ps_cnt;
	int cnt_blk;

	ps_cnt=0;
	cnt_blk=count_blk(bk,1);
	for(r=1-BR;r<MR;++r) {
		for(c=1-BC;c<MC;++c) {
			set_matrix(ch,0);
			locate(ch,r,c,bk);
			if(count_mat(ch,1)==cnt_blk)
				copy_matrix(fc[ps_cnt++],ch);
		}
	}
	return ps_cnt;
}

int make_full_choices(mat_type fc[])
{
	static cel_type blocks[][BR][BC] = {
		{{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0}},
		{{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
		{{1,1,1,0},{0,1,0,0},{0,0,0,0},{0,0,0,0}},
		{{1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}},
		{{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
		{{1,0,0,0},{1,0,0,0},{1,1,0,0},{0,0,0,0}},
		{{1,1,1,0},{0,0,1,0},{0,0,0,0},{0,0,0,0}}
	};
	static const int num_blocks=sizeof(blocks)/sizeof(blocks[0]);
	blk_type bk;
	int i,rt;
	int fc_cnt;

	fc_cnt=0;
	for(i=0;i<num_blocks;++i) {
		copy_block(bk,blocks[i]);
		for(rt=0;rt<4;++rt) {
			fc_cnt+=possible_locations(fc+fc_cnt,bk);
			rotate_cw(bk);
		}
	}
	fc_cnt=erase_duplication(fc,fc_cnt);
	return fc_cnt;
}

void set_matrix_num(mat_type m,cel_type val_1,cel_type val_2,int num_value1)
{
	int r,c;
	int cnt;

	cnt=0;
	for(r=0;r<MR;++r) 
		for(c=0;c<MC;++c)
			m[r][c]=(cnt++<num_value1 ? val_1 : val_2);
}

void shuffle_matrix(mat_type m)
{
	int r,c;
	int rand_r,rand_c;
	cel_type temp;

	for(r=0;r<MR;++r) {
		for(c=0;c<MC;++c) {
			rand_r=rand()%MR;
			rand_c=rand()%MC;
			temp=m[r][c];
			m[r][c]=m[rand_r][rand_c];
			m[rand_r][rand_c]=temp;
		}
	}
}

void random_matrix(mat_type m,cel_type val_1,cel_type val_2,int num_val_1)
{
	set_matrix_num(m,val_1,val_2,num_val_1);
	shuffle_matrix(m);
}

int copy_matrix_list(mat_type ml_dst[],mat_type ml_src[],int ml_num)
{
	int i;

	/* 여기에 적당한 코드를 채워라 */
	for(i=0;i<ml_num;++i)
	{
		copy_matrix(ml_dst[i],ml_src[i]);
	}
	
	return i;
}

int is_overlap(mat_type m1,mat_type m2)
{
	int r,c;

	for(r=0;r<MR;++r) 
		for(c=0;c<MC;++c)
			if(m1[r][c]!=0 && m2[r][c]!=0)
				return 1;
	return 0;
}

int erase_impossible(mat_type ml[],int ml_num,mat_type m)
{
	int i;

	/* 여기에 적당한 코드를 채워라 */
	for(i=0;i<ml_num;++i){
		if(is_overlap(ml[i],m)) {
			erase_matrix(ml,ml_num,i);
			ml_num--;
			i--;
		}
	}

	return ml_num;
}

void print_matrix_list(mat_type ml[],int ml_num)
{
	int i;

	for(i=0;i<ml_num;++i) {
		printf("matrix #%d\n",i);
		print_matrix(ml[i]);
		printf("\n");
	}
}

int valid_block(int r1,int c1,int r2,int c2,int r3,int c3,int r4,int c4)
{
	return 
		0<=r1 && r1<MR && 0<=c1 && c1<MC &&
		0<=r2 && r2<MR && 0<=c2 && c2<MC &&
		0<=r3 && r3<MR && 0<=c3 && c3<MC &&
		0<=r4 && r4<MR && 0<=c4 && c4<MC;
}

void get_matrix_from_string(char* str,mat_type t)
{
	int r1,r2,r3,r4;
	int c1,c2,c3,c4;

	sscanf(str," %d %d %d %d %d %d %d %d ",
		&r1,&c1,&r2,&c2,&r3,&c3,&r4,&c4);
	set_matrix(t,0);
	
	if(valid_block(r1,c1,r2,c2,r3,c3,r4,c4)) {
		t[r1][c1]=1;
		t[r2][c2]=1;
		t[r3][c3]=1;
		t[r4][c4]=1;
	}
}

int get_block(mat_type poss_cho[],int pc_num,mat_type full_cho[],int fc_num)
{
	cel_type t[MR][MC];
	char line[1024];
	char cmd[1024];
	int pc_id,fc_id;

	while(1) { /* 무한 LOOP: 잘못된 입력일 경우 계속 반복한다. */
		printf(" [Team #02] Input >> ");
		fflush(stdin);
		gets(line);

		strcpy(cmd,line);

		if(strcmp(cmd,"back")==0) { /* 일반 명령어가 입력된 경우 */
			return CMD_BACK;
		}
		else if(strcmp(cmd,"quit")==0) { /* 일반 명령어가 입력된 경우 */
			return CMD_QUIT;
		}
		else if(cmd[0]=='#') {
			/* full choice id가 입력된 경우				*/
			/* 여기를 적당한 코드로 채워라				  */
			/* 바람직한 full choice id가 입력된 경우에만  */
			/* 이에 해당하는 possible choice id 리턴한다. */
			sscanf(cmd,"#%d",&fc_id);
			if(fc_id>=0 && fc_id<fc_num)
			{
				copy_matrix(t,full_cho[fc_id]);
				pc_id=find_matrix(poss_cho,pc_num,t);
				if(pc_id<pc_num) return pc_id; 
				else
					printf(" Not Found choice_id \n");
			}
			else
				printf(" Choice_id Is Wrong\n");

		}
		else { /* matrix의 cell list가 입력된 경우 */
			/* 여기를 적당한 코드로 채워라                */
			/* 바람직한 cell list가 입력된 경우에만       */
			/* 이에 해당하는 possible choice id 리턴한다. */
			/* cell list는 정수 8개((row,column) x 4개)를 */
			/* 입력받는다.				*/
			if(strlen(cmd)!=15) printf("  Input is Not Correct \n");
			else {
				get_matrix_from_string(cmd,t);
				pc_id=find_matrix(poss_cho,pc_num,t);
				if(pc_id<pc_num) return pc_id; 
				else printf(" Not Found choice_id \n");
			}
		}
	}
	return pc_num; /* 아무 의미 없는 리턴 */
}

void matrix_reset(mat_type dst,mat_type src)
{
	int r,c;
	for(r=0;r<MR;r++)
		for(c=0;c<MC;c++){
			if(src[r][c]==1)
				dst[r][c]=src[r][c];
		}
}

void add_matrix(mat_type dst,mat_type src)
{
	int r,c;

	for(r=0;r<MR;r++)
		for(c=0;c<MC;c++){
			if(src[r][c]==1)
				dst[r][c]+=src[r][c];
		}
}

void subtract_matrix(mat_type dst,mat_type src)
{
	int r,c;
	for(r=0;r<MR;r++)
		for(c=0;c<MC;c++){
			if(src[r][c]==1)
				dst[r][c] = dst[r][c] - src[r][c];
		}
}

void shuffle_choices(mat_type poss_cho[],int pc_num) 
{
	int i,rand_i;
	mat_type temp;

	for(i=0;i<pc_num;++i) 
	{
		rand_i=rand()%pc_num;
		copy_matrix(temp,poss_cho[i]);
		copy_matrix(poss_cho[i],poss_cho[rand_i]);
		copy_matrix(poss_cho[rand_i],temp);
	}
} 

int win(mat_type poss_cho[],int pc_num,mat_type* full_cho,
		int fc_num,mat_type new_mat,time_t limit) 
{
	int pc_id=0,i,ret_val;
	int pnum=pc_num,
		fnum=fc_num;

	if(time(NULL)>=limit) return -1;

	for(i=0;i<pnum;++i) 
	{
		if(!is_overlap(new_mat,poss_cho[i])) 
		{
			add_matrix(new_mat,poss_cho[i]);
			ret_val = win(poss_cho,pnum,full_cho,fnum,new_mat,limit);
			subtract_matrix(new_mat,poss_cho[i]);
			if(ret_val<0) return -1;
			if(ret_val==0) return 1;
		}
	}
	return 0; 
}


int computer_choice(mat_type* poss_cho,int pc_num,
					mat_type* full_cho,int fc_num,mat_type current_mat)
{
	int pc_id=0,ret_val=0,i;


	shuffle_choices(poss_cho,pc_num);
	for(i=0;i<pc_num;++i) 
	{
		add_matrix(current_mat,poss_cho[i]);
		ret_val = win(poss_cho,pc_num,full_cho,fc_num,current_mat,time(NULL)+10);
		subtract_matrix(current_mat,poss_cho[i]);
		if(ret_val==0){
			printf(" Maybe Computer Win \n");
			return i;
		}
		if(ret_val<0)
		{
			printf("Time Break Exception\n");
			pc_id = rand()%pc_num;
			return pc_id;
		}
	}

	printf(" Maybe Player Win\n");
	pc_id = rand()%pc_num;

	return pc_id;
}

int load_table(char* filename, mat_type mat)
{
	FILE* fp;
	int r,c;
	fp = fopen(filename,"rt");
	if(fp == NULL)
	{
		printf(" File Not Found\n");
		return -1;
	}
	for(r=0;r<MR;++r)
		for(c=0;c<MC;++c)
		{
			if( fscanf(fp,"%d",&mat[r][c]) !=1)
				return -2;
		}
	fclose(fp);
	return 0;
}


/////////////////////////////////////////////////////////바이너리 처리용////////////////////////////////////////

bin_type matrix_to_binary(mat_type mat) /*매트릭스를 바이너리로 변환후 리턴*/
{
	int r,c;
	bin_type bin;
	bin=0;
	for(r=0;r<MR;r++)
		for(c=0;c<MC;c++)
		{
			bin *=(bin_type)2;
			bin +=(bin_type)mat[r][c];
		}
	return bin;
}

void binary_to_mat(bin_type bin,mat_type m1)/*바이너리를 매트릭스로*/
{
	int r,c;

	for(r=MR-1;r>=0;--r)
	{
		for(c=MC-1;c>=0;--c)
		{
			m1[r][c] = (int)bin%2 ;
			bin /= 2;
		}
	}
}

int copy_matlist_to_binlist(mat_type* mlist, int ml_num, bin_type* blist)/*리스트에 저장된 매트릭스를 바이너리형식으로 바꿔 저장*/
{
	int bl_num;
	
	for(bl_num=0;bl_num<ml_num;bl_num++)
	{
		blist[bl_num] = matrix_to_binary( mlist[bl_num] );
	}

	return bl_num;
}


int copy_binlist(bin_type* dstlist, bin_type* srclist, int src_num)/*바이너리 리스트끼리 복사*/
{
	int i;
	for(i=0;i<src_num;++i)
		dstlist[i]=srclist[i];
	return i;
}


int bin_find(bin_type* blist, int bl_num, bin_type bin)/*바이너리 리스트에서 특정 원소찾기*/
{
	int i;
	for(i=0;i<bl_num; ++i)
		if( blist[i]==bin )
			return i;
	return i;
}


int bin_erase(bin_type* blist, int bl_num, int idx)/*bin리스트서 원소하나 삭제후 원소개수 반환*/
{
	blist[idx]=blist[--bl_num];

	return bl_num;
}



int bin_erase_impossible(bin_type current_table, bin_type* poss_cho_bin, int pcb_num)/*넣을수 없는 bin제거*/
{
	int i;

	for(i=0;i<pcb_num; ++i)
		if( current_table&poss_cho_bin[i] )
			poss_cho_bin[i--]=poss_cho_bin[--pcb_num];

	return pcb_num;
}


int bin_win(bin_type current_table, bin_type* poss_cho_bin, int pcb_num, time_t limit)
{
	int i;
	int result;

	if( time(NULL) >= limit )
		return -1; /*시간 초과시 -1 리턴*/

	for(i=0;i<pcb_num;++i)
	{
		if( (current_table& (*(poss_cho_bin+i)) )==0 )
		{
			current_table^= (*(poss_cho_bin+i));
			result = bin_win( current_table, poss_cho_bin, pcb_num, limit);
			current_table^= (*(poss_cho_bin+i));
			if(result < 0) return -1;
			if(result ==0) return 1;
		}
	}
	return 0;
}

int nonR_bin_win(bin_type current_table, bin_type* poss_cho_bin, int pcb_num, time_t limit)
{
	bin_type* cl;
	bin_type* cl_end;
	bin_type* stack[1024];
	int top=0;
	int ret_val;

	cl_end = poss_cho_bin+pcb_num;

CALL1:	for(cl=poss_cho_bin;cl!=cl_end;++cl)
	{
		if( time(NULL) >= limit ) return -1;
		if(current_table & *cl) continue;
		current_table ^= *cl;
		stack[top++] = cl;
		goto CALL1;
RET1:		cl=stack[--top];
		current_table ^= *cl;
		if(ret_val==-1) return -1;
		if(ret_val) continue;
		if(top==0) return 1;
		ret_val = 1;
		goto RET1;
	}
	if(top==0) return 0;
	ret_val = 0;
	goto RET1;
}


int bin_computer_choice(bin_type current_table, bin_type* poss_cho_bin, int pcb_num)
{
	int i,pc_id=0;
	int win;
	int list[32] = {0,8,9,17,18,26,27,35,36,37,
				38,39,40,41,72,73,74,75,76,77,
				78,85,118,125,486,494,543,617,624,
				699,735,742};
	int list_num =32,count=0,rand_i=0;
	time_t limit;

	limit = time(NULL)+10;

	for(i=0;i<pcb_num;++i)
	{
		if( (current_table & (*(poss_cho_bin+i)) ) == 0 )
		{
			current_table^= (*(poss_cho_bin+i));
			win=bin_win(current_table, poss_cho_bin, pcb_num, limit);
			current_table^= (*(poss_cho_bin+i));
			if(win == -1)
			{
				printf("\n Time Over : Unkown Choice\n\n");
				/*while(1)
				{
					count++;
					if(count==32) return rand()%pc_num;
					rand_i = rand()%list_num;
					if( (current_table & (poss_cho_bin[find_bin(list[rand_i]])) == 0 )
					{
						return bin_find_i;
					}
				}*/
				return rand()%pcb_num;

			}
			else if(win == 0)
				return i;
		}
	}
	printf("\n Random Choice\n\n");
	return rand()%pcb_num;
}


///////////////////////////////////////////////////메인////////////////////////////////////////////////////////

int main(void)
{
	mat_type full_cho[1500]; /* the list of full choices */
	mat_type poss_cho[1024]; /* the list of possible choices */
	mat_type current_mat,temp_mat;
	mat_type back_mat[15];
	int fc_num;
	int pc_num;
	int ret_val;
	int back_num=0;
	int pcb_num;

	bin_type current_table;
	bin_type poss_cho_bin[1024];

	
	int who;
	int input=2;
	char name[80];

	fc_num=make_full_choices(full_cho);
	pc_num=copy_matrix_list(poss_cho,full_cho,fc_num);
	
	printf(" ******* Blank Painting Game [7][9] *******\n \
Team #02 : Kim YoSep, Park KyungMin, Go ByoungHoon \n \
The Limit of Time = 10 second(s)\n \
Full Choices = %d\n\n", fc_num);

	srand((unsigned)time(NULL));

	while(input != 0 && input != 1)
	{
		printf(" Choose a Initial Table (File:0, Random : 1) >> ");
		scanf("%d",&input);
	}

	while(input==0)
	{
		printf(" Input the File Name >> ");
		fflush(stdin);
		gets(name);
		input = load_table(name,current_mat);
		if(input != -1) input=2;
		else input =0 ;
	}
	if(input==1)
	{
		printf(" Random Matrix \n");
		random_matrix(current_mat,1,0,5);
	}

	printf(" Input Turn (COMPUTER: 0, HUMAN: 1) >> ");
	scanf("%d",&who);
	
	printf("\n");

	pc_num=erase_impossible(poss_cho,pc_num,current_mat);
	shuffle_choices(poss_cho,pc_num);

	print_matrix(current_mat);
	printf(" Num. of PC = %d\n\n",pc_num);
	if(who==0) goto L1;

	/*대결부분*/
	while(1){

		if (pc_num==0) {printf(" winner is computer!!\n"); break;}

		ret_val=get_block(poss_cho,pc_num,full_cho,fc_num);

		if(ret_val==CMD_BACK) {
			if(back_num==0) printf(" Back_Error\n");
			else{
				--back_num;
				printf(" ret_val: CMD_BACK\n");
				copy_matrix(current_mat,back_mat[back_num]);
			}
			continue;
		}
		else if(ret_val==CMD_QUIT) {
			printf(" ret_val: CMD_QUIT\n");
			break;
		}
		else{
			copy_matrix(back_mat[back_num],current_mat);
			++back_num;

			matrix_reset(current_mat,poss_cho[ret_val]);
			printf("\n  (Human Choice) \t (Current Table) \n");
			print_matrix_2(poss_cho[ret_val],current_mat);
			copy_matrix(temp_mat,poss_cho[ret_val]);
			pc_num=erase_impossible(poss_cho,pc_num,current_mat);
			printf("  FC-ID = %d \t\t  Num. of PC = %d\n\n",
				find_matrix(full_cho,fc_num,temp_mat),pc_num
			);
		}
		
L1:

		/*컴퓨터 선택*/
		pcb_num=copy_matlist_to_binlist(poss_cho,pc_num,poss_cho_bin);
	
		/*컴퓨터 패배*/
		if (pc_num==0) {printf(" Computer Lose.\n"); break;}

		current_table = matrix_to_binary(current_mat);
		ret_val=bin_computer_choice(current_table,poss_cho_bin,pcb_num);
		matrix_reset(current_mat,poss_cho[ret_val]);
		

		printf("  (Computer Choice) \t (Current Table)\n");
		print_matrix_2(poss_cho[ret_val],current_mat);
		copy_matrix(temp_mat,poss_cho[ret_val]);
		pc_num=erase_impossible(poss_cho,pc_num,current_mat);
		printf("  FC-ID = %d \t\t  Num. of PC = %d\n\n",
			find_matrix(full_cho,fc_num,temp_mat),pc_num
		);
		
	}

	return 0;
}