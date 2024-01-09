#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Include ctype.h for character type functions

char* concatenate_and_manipulate(char* str1, char* str2) {
	int n1= strlen(str1);
	int n2= strlen(str2);
	int size=n1+n2+2;
	
	char* _s = (char*)malloc(size*sizeof(char));

	strcpy(_s,str1);
	strcat(_s,"_");
	strcat(_s,str2);
	
	return _s;
}