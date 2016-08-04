#include <stdio.h>

int main(void){
	int troco;
	printf("Digite a quantidade de troco: ");
	scanf("%d",&troco);
	int nro_moedas = 0;
	nro_moedas+= troco/100;
	troco = troco % 100;
	nro_moedas+= troco/50;
	troco = troco%50;
	nro_moedas+= troco/25;
	troco = troco%25;
	nro_moedas+= troco/10;
	troco = troco % 10;
	nro_moedas+= troco/5;
	troco = troco % 5;
	nro_moedas+= troco/1;
	printf("Total de moedas: %d.\n",nro_moedas);c
	return 0;
}