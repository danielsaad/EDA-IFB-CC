Este programa exemplifica os conceitos de modularização ao separar os módulos
das estruturas triângulo e quadrado.

Para gerar o executável é necessário compilar todos os fontes em arquivos objetos
e depois ligá-los.
#Compilação

Para compilar faça:
```shell
	gcc -c quadrado.c triangulo.c main.c
	gcc main.o quadrado.o triangulo.o -o main -lm
```