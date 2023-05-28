#ifndef TRIANGULO_H_INCLUDED
#define TRIANGULO_H_INCLUDED

typedef struct triangulo_t{
	double a,b,c;
}triangulo_t;

triangulo_t cria_triangulo(void);
double area_triangulo(triangulo_t t);

#endif