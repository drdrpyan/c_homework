#include <stdio.h>

/* (0,0)���� (x,y)�� ������ �������� */
/* ��(x1,y1)�� ���ʿ� ������ ���� ������ ��ȯ */
/* ��(x1,y1)�� �����ʿ� ������ ���� ������ ��ȯ */
/* ��(x1,y1)�� ���� ���� ������ 0(zero)�� ��ȯ */

int side(int x, int y, int x1, int y1)
{
	int s=0;
	s=(x*y1*y)-(x1*y*y);
	return s;
}

int main(void)
{
	int px, py, qx, qy;
	int s;

	printf("input coordinates: ");
	scanf(" %d %d %d %d", &px, &py, &qx, &qy);

	s=side(px, py, qx, qy);
	if(s>0) printf("left side\n");
	else if(s<0) printf("right side\n");
	else printf("on the line\n");

	return 0;
}