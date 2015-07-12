#include <stdio.h>

void set(int a[])/*1�� �迭 11ĭ�� 0���� �ʱ�ȭ�Ͽ� ����*/
{
	int i;
	for(i=0;i<11;i++)
		a[i]=0;
}

void copy(int a[] , int b[] )/* �迭a�� �迭b�� ���� */
{
	int i;
	for (i=0;i<11;i++)
		a[i] =b[i];
}

int valid1(int n, int a[])/*0x07�� a�� n��° ĭ���� ����־����� ��ȿ���� Ȯ��*/
{
	if (n>9) return 0;
	if ((a[n]+a[n+1]+a[n+2])==0) return 1;
	return 0;
}
int valid2(int n, int a[]) /*0x31�־����� ��ȿ���� Ȯ��*/
{
	if(n>5) return 0;
	if((a[n]+a[n+4]+a[n+5])==0) return 1;
	return 0;
}
int valid3(int n, int a[]) /*0x15�־����� ��ȿ���� Ȯ��*/
{
	if(n>6) return 0;
	if((a[n]+a[n+2]+a[n+4])==0) return 1;
	return 0;
}

void put1(int n,int a[]) /*0x07�� a�� n��°���� ����*/
{
	a[n]=a[n+1]=a[n+2]=1;
}
void put2(int n,int a[]) /*a�� 0x31����*/
{
	a[n]=a[n+4]=a[n+5]=1;
}
void put3(int n,int a[]) /*a�� 0x15 ����*/
{
	a[n]=a[n+2]=a[n+4]=1;
}
int win(int a[]){
	int b[11];
	int i=0 ;
	int ret= 0;
	set(b);

	for(i=0 ; i< 11 ; i++){
		if ( valid1(i,a) ){
			copy(b,a);
			put1(i,b);
			ret|= !win(b);
		}
		if ( valid2(i,a) ){
			copy(b,a);
			put2(i,b);
			ret|= !win(b);
		}
		if ( valid3(i,a) ){
			copy(b,a);
			put3(i,b);
			ret|= !win(b);
		}
	}
	return ret;
}
int main(void){
	int a[11];
	set(a);	
	printf("%d\n",win(a));
	return 0;
}