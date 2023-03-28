#include <stdio.h>
#include <stdlib.h>

int main(void){
	char* buf;
	buf = malloc(1LL << 60);
	fgets(buf,1024,stdin);
	printf("buf = %s\n",buf);
	return 0;
}
