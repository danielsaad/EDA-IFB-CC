#ifndef QUADRADO_H_INCLUDED
#define QUADRADO_H_INCLUDED

typedef struct quadrado_t{
	double l;
}quadrado_t;

quadrado_t cria_quadrado(void);
double area_quadrado(quadrado_t q);

#endif
