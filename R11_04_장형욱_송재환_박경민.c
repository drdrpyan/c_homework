#include <stdio.h>

char * strnset(char *str, int ch, int n){  //3번
	int i;
	for(i=0; i<n; ++i){
		if(!str[i])	return str;
		str[i]=ch;
	}	
	return str;
}

char * strcat(char* dst, char* src){  //5번
	int i, j;
	for(i=0; dst[i]; ++i);
	for(j=i; src[j-i]; ++j)
		dst[j]=src[j-i];
	dst[j] = '\0';
	return dst;
}

char* strrev(char *str){  // 6번	 
	int i, j;
	char temp;
	for(i=0; str[i]; i++);
	for(j=0; j<i/2; ++j){
		temp = str[j];
		str[j] = str[i-1-j];
		str[i-1-j] = temp;
	}

	return str;
}

int strcspn(char* str, char* set){ // 9번
	int i, j;
	for(i=0; str[i]; ++i){
		for(j=0; set[j]; ++j){			
			if(set[j] == str[i]) return i;		
		}
	}
	return i;
}

char * strstr(char* str, char* sub){ // 10번
	int i, j;
	for(i=0; str[i]; ++i){
		for(j=0;str[i+j]==sub[j];j++);
		if(sub[j]==0){
			for(j=0;str[j];j++) str[j]=str[j+i];
			str[j]=0;
			return str;
		}
	}
	return 0;
}

int main(){
	{ //3번
		char a[5] = "abcd";
		printf("%s\n", strnset(a, 'e', 2) );
	}

	{ //5번
		char a[10] = "123";
		char b[10] = "abcdef";

		strcat(a, b);
		printf("%s\n", a);
	}

	{ //6번
		char a[10] = "abcd";
		strrev(a);
		printf("%s\n", a);
	}

	{ //9번
		char a[10] = "abcdefghi";
		printf("%d\n", strcspn(a, "fd"));
	}

	{ //10번
		char a[20] = "abcedbcdeabce";
		printf("%s\n", strstr(a, "ced"));
	}
	return 0;
}