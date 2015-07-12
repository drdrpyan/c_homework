#include <stdio.h>
#include <time.h>

int check(int n,int c,int i)
{
	return n>=i && c!=i;
}

/* R15_apple_subtraction.c에 있는 win9을 수정함 */
int win10(int n,int p,int d,time_t limit)
{
	int c;
	int i;
	int ret_val;
	
	if(time(NULL)>=limit) return -1;
	c=(p+d)%3+1;
	for(i=1;i<=3;++i) {
		if(check(n,c,i)) {
			ret_val=win10(n-i,i,d+1,limit);
			if(ret_val<0) return -1;
			if(!ret_val) return 1;
		}
	}
	return 0;
}

int main(void)
{
	int i;
	int ret_val;

	for(i=1;i<100;++i) {
		ret_val=win10(i,0,1,time(NULL)+10); /* 10초 이상 지나면 중단 */
		printf("win(%d)=%s\n",i,
			(ret_val<0 ? "break" : (ret_val==0 ? "false" : "true") ));
	}
	return 0;
}
