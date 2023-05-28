#include <stdio.h>
#include "quadrado.h"
#include "triangulo.h"

int main(){
	triangulo_t t = cria_triangulo();
	quadrado_t q  = cria_quadrado();
	printf("Área do triângulo = %lf.\n",area_triangulo(t));
	printf("Área do quadrado = %lf.\n",area_quadrado(q));
	return 0;
}
