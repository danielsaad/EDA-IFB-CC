#include <stdio.h>

int main(void){
	int troco;
	printf("Digite a quantidade de troco: ");
	scanf("%d",&troco);
	int nro_moedas = 0;
	while(troco>0){
		/* Utilizamos a moeda de um real */
		if(troco>=100){
			nro_moedas = troco/100;
			troco= troco%100;
		}
		else if(troco>=50){
			troco-=50;
			nro_moedas++;
		}
		else if(troco>=25){
			troco-=25;
			nro_moedas++;
		}
		else if(troco>=10){
			troco-=10;
			nro_moedas++;
		}
		else if(troco>=5){
			troco-=5;
			nro_moedas++;
		}
		else if(troco>=1){
			troco-=1;
			nro_moedas++;
		}
	}
	printf("Total de moedas: %d.\n",nro_moedas);
	return 0;
}