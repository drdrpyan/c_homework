#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


#define MR				7
#define MC				7
#define BR				4
#define BC				4

#define CMD_BACK		-1
#define CMD_QUIT		-2

typedef int cel_type;
typedef cel_type mat_type[MR][MC];
typedef cel_type blk_type[BR][BC];

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

int erase_duplication(mat_type ml[],int ml_num)
{
	int i,ml_id;

	for(i=0;i<ml_num;++i) {
		while((ml_id=find_matrix(ml+i+1,ml_num-i-1,ml[i]))<ml_num-i-1) {
			erase_matrix(ml+i+1,ml_num-i-1,ml_id);
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
		printf("Input block >> ");
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
				printf(" choice_id is wrong\n");

		}
		else { /* matrix의 cell list가 입력된 경우 */
			/* 여기를 적당한 코드로 채워라                */
			/* 바람직한 cell list가 입력된 경우에만       */
			/* 이에 해당하는 possible choice id 리턴한다. */
			/* cell list는 정수 8개((row,column) x 4개)를 */
			/* 입력받는다.				*/
			if(strlen(cmd)!=15) printf("wrong input\n");
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
int win(mat_type* poss_cho,int pc_num,mat_type* full_cho,int fc_num,mat_type current_mat,time_t limit)
{
	int pc_id,i,ret_val;
	int pnum=pc_num,
		fnum=fc_num;
	
	fc_num=make_full_choices(full_cho);
	pc_num=copy_matrix_list(poss_cho,full_cho,fnum);
	pc_num=erase_impossible(poss_cho,pnum,current_mat);

	//printf("call\n");
	if(pc_num==0){
		//printf("I'm Rooser\n");
		return -1;
	}

	if(time(NULL)>=limit) {
		printf("Time Exception Break\n");
		pc_id=rand()%pc_num;
		return pc_id;
	}
	
	for(i=0;i<pc_num;++i) 
	{
		matrix_reset(current_mat,poss_cho[i]);
		ret_val=win(poss_cho,pnum,full_cho,fnum,current_mat,limit);
	}

	if(ret_val<0) return -1;
	return i;
}
int computer_choice(mat_type* poss_cho,int pc_num,
					mat_type* full_cho,int fc_num,mat_type c_mat)
{
	int pc_id;
	mat_type current_mat;
	copy_matrix(current_mat,c_mat);

	if(win(poss_cho,pc_num,full_cho,fc_num,current_mat,time(NULL)+10)<0)
	{
		pc_id=rand()%pc_num;
		return pc_id;
	}
	else pc_id = win(poss_cho,pc_num,full_cho,fc_num,c_mat,time(NULL)+10);

	return pc_id;
}

int main(void)
{
	mat_type full_cho[1024]; /* the list of full choices */
	mat_type poss_cho[1024]; /* the list of possible choices */
	mat_type current_mat;
	mat_type back_mat[10];
	int fc_num;
	int pc_num;
	int ret_val;
	int back_num=0;
	
	int who;

	printf("Who first start?? \n1.player 2.computer\n");
	scanf("%d",&who);
	srand((unsigned)time(NULL));
	random_matrix(current_mat,1,0,5);
	fc_num=make_full_choices(full_cho);
	if(who==2) goto L1;
	while(1){
		print_matrix(current_mat);
		printf("\n");
		fc_num=make_full_choices(full_cho);
		pc_num=copy_matrix_list(poss_cho,full_cho,fc_num);
		pc_num=erase_impossible(poss_cho,pc_num,current_mat);

		if (pc_num==0) {printf("winner is computer!!\n"); break;}

		printf("the number of full choices = %d\n",fc_num);
		printf("the number of possible choices = %d\n\n",pc_num);

		ret_val=get_block(poss_cho,pc_num,full_cho,fc_num);

		if(ret_val==CMD_BACK) {
			if(back_num==0) printf("Back_Error\n");
			else {
				--back_num;
				printf("\nret_val: CMD_BACK\n");
				copy_matrix(current_mat,back_mat[back_num]);
			}
			continue;
		}
		else if(ret_val==CMD_QUIT) {
			printf("\nret_val: CMD_QUIT\n");
			break;
		}
		else{
			printf("\nret_val: possible choice ID = %d\n",ret_val);
			printf("full choice ID of your block = %d\n\n",
				find_matrix(full_cho,fc_num,poss_cho[ret_val])
			);
			copy_matrix(back_mat[back_num],current_mat);
			++back_num;
			print_matrix(poss_cho[ret_val]);
			matrix_reset(current_mat,poss_cho[ret_val]);			
		}
		
L1:
		print_matrix(current_mat);
		printf("\n");

		fc_num=make_full_choices(full_cho);
		pc_num=copy_matrix_list(poss_cho,full_cho,fc_num);
		pc_num=erase_impossible(poss_cho,pc_num,current_mat);
	
		if (pc_num==0) {printf("winner is Player!!\n"); break;}

		printf("the number of full choices = %d\n",fc_num);
		printf("the number of possible choices = %d\n\n",pc_num);


		ret_val=computer_choice(poss_cho,pc_num,full_cho,fc_num,current_mat);
		printf("\nret_val: possible choice ID = %d\n",ret_val);
		printf("full choice ID of your block = %d\n\n",
			find_matrix(full_cho,fc_num,poss_cho[ret_val])
		);
		print_matrix(poss_cho[ret_val]);
		matrix_reset(current_mat,poss_cho[ret_val]);
	}

	return 0;
}
	