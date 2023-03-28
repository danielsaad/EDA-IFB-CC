#include <stdio.h>
#include <stdlib.h>


char* my_getline(void){
	char c;
	char* s = calloc(1,sizeof(char));
	int tam = 1;
	int i = 0;
	while( (c=getchar())!='\n' ){
		s[i] = c;
		i++;
		if(i==tam){
			s = realloc(s,(tam+1)*sizeof(char));
			tam++;
		}
	}
	s[tam-1] = '\0';
	return s;
}

int main(void){
	char* s = my_getline();
	printf("String lida = %s\n",s);	
	return 0;
}