#include <stdio.h>
#include <stdlib.h>

char *my_getline(void) {
    char *str;
    char ch;
    str = calloc(1, sizeof(char));
    int tam = 0;
    int cap = 1;
    while ((ch = getchar()) != '\n') {
		if (cap == tam) {
			cap *=2;
            str = realloc(str,cap*sizeof(char));
        }
		str[tam] = ch;
        tam++;
    }
	str = realloc(str,(tam+1)*sizeof(char));
    str[tam] = '\0';
	return str;
}


int main(void){
	char* str = my_getline();
	printf("A string lida é: %s\n",str);
	free(str);
	return 0;
}