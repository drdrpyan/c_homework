#include <stdio.h>

int strlen(char* str)
{
	int i;

	for(i=0;str[i];++i)
		;
	return i;
}

char* strset(char* str,int ch)
{
	int i;

	for(i=0;str[i];++i)
		str[i]=ch;
	return str;
}

char* strnset(char* str,int ch,int n) /* report */
{
	int i;
	return str;
}

char* strcpy(char* dst,char* src)
{
	int i;

	for(i=0;dst[i]=src[i];++i)
		;
	return dst;
}

char* strcat(char* dst,char* src) /* report */
{
	int i,j;
	return dst;
}

char* strrev(char* str) /* report */
{
	int i,j;
	char temp;
	return str;
}

int strcmp(char* str1,char* str2)
{
	int i;

	for(i=0;str1[i] || str2[i];++i) {
		if(str1[i]>str2[i]) 
			return 1;
		if(str1[i]<str2[i]) 
			return -1;
	}
	return 0;
}

char* strchr(char* str,int ch)
{
	int i;

	for(i=0;str[i];++i)
		if(str[i]==ch) 
			return str+i;
	return 0;
}

int strcspn(char* str,char* set) /* report */
{
	int i,j;
	return i;
}

char* strstr(char* str,char* sub) /* report */
{
	int i,j;
	return 0;
}

int main(void)
{
	char a[10]="abcd";
	char b[4]="123";

	printf("%d\n",strlen(a));
	printf("%s\n",strset(a,'e')); 
	printf("%s\n",strnset(a,'a',2));
	printf("%s\n",strcpy(a,b));
	printf("%s\n",strcat(a,b));
	printf("%s\n",strrev(a));
	printf("%d\n",strcmp(a,b));
	printf("%c\n",*strchr(a,'2'));
	printf("%d\n",strcspn(a,"21"));
	printf("%s\n",strstr(a,"13"));

	return 0;
}
