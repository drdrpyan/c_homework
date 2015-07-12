#include <stdio.h>


/* 巩力3 */
char * strnset(char *str, int ch, int n)
{
	int i;
	for(i=0; i<n; i++) str[i]=ch;

	return str;
}

/* 巩力5 */
char* strcat(char* dst,char* src)
{
	int i,j;
	for(i=0; dst[i]!=0; i++)
		;
	for(j=0; src[j]!=0; j++)
		dst[i+j]=src[j];

	return dst;
}

/* 巩力6 */
char* strrev(char* str)
{
	int i,j;
	char temp;
	for(j=0; str[j]!=0; j++);
	for(i=0,j=j-1; i<=j; i++,j--)
	{
		temp=str[i];
		str[i]=str[j];
		str[j]=temp;
	}
	
	return str;
}

/* 巩力9 */
int strcspn(char* str, char* set)
{
	int i,j;
	for(i=0; str[i]!=0; i++)
		for(j=0; set[j]!=0; j++)
			if(str[i]==set[j]) return i;

	return i;

}

/* 巩力 9_2
int strcspn(char* str, char* set)
{
	int i,j;
	for(j=0; set[j]!=0; j++)
		for(i=0; str[i]!=set[j]; i++)
			;

	return i;
}
*/


/* 巩力10 */
char* strstr(char* str,char* sub)
{
	int i,j;
	for(i=0; str[i]!=0; i++)
	{
		for(j=0; str[i+j]==sub[j]; j++)
			;
		if(sub[j]==0)
		{
			for(j=0; str[j]!=0; j++)
				str[j]=str[i+j];
			str[j]=0;
			return str;
		}
	}

	return 0;
}




int main(void)
{
	char a[20]="abcabcdeabce";

	printf("%s\n", strstr(a,"cd"));

	return 0;

}