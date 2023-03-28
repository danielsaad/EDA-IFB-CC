#include <stdio.h>

int moedas(int troco){
	if(troco == 0){
		return 0;
	}
	else if(troco>=100){
		return troco/100 + moedas(troco%100);
	}
	else if(troco>=50){
		return 1 + moedas(troco - 50);
	}
	else if(troco>=25){
		return 1 + moedas(troco - 25);
	}
	else if(troco >=10){
		return 1 + moedas(troco - 10);
	}
	else if(troco>=5){
		return 1 + moedas(troco -5);
	}
	else{
		return 1 + moedas(troco -1);
	}
}


int main(void){
	int troco;
	printf("Digite a quantidade de troco: ");
	scanf("%d",&troco);
	printf("Total de moedas: %d.\n",moedas(troco));
	return 0;
}