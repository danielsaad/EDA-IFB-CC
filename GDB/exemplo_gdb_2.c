# include <stdio.h>

int main(){
	int i, num, j;
	printf ("Digite o número: ");
	scanf ("%d", &num );

	for (i=1; i<num; i++){
		j=j*i;    
	}

	printf("Fatorial de %d é %d\n",num,j);
}