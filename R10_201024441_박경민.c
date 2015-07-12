#include <stdio.h>

/* (0,0)에서 (x,y)로 직선을 기준으로 */
/* 점(x1,y1)이 왼쪽에 있으면 양의 정수를 반환 */
/* 점(x1,y1)이 오른쪽에 있으면 음의 정수를 반환 */
/* 점(x1,y1)이 직선 위에 있으면 0(zero)를 반환 */

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