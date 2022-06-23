# Estruturas de Dados e Algoritmos

Material auxiliar pra disciplina de Estruturas de Dados e Algoritmos do curso
de Ciência da Computação do IFB-Taguatinga.

## Compilação para Linux

### Pré-Requisitos
Para compilar os executáveis e a biblioteca você deverá possuir o make e o gcc
instalados.

### Compilação

```shell
make
```

Após isso os cabeçalhos estarão na pasta `include` e a biblioteca estática
estará na pasta `lib`. Desta forma, para utilizar a biblioteca em seu projeto,
basta utilizar esses dois recursos.

#### Exemplos

Para compilar os exemplos, basta fazer:

```shell
make examples
```

Os exemplos estarão dispostos na pasta `bin`

#### Testes

Um conjunto de testes unitários sobre a biblioteca foi criado através do
Framework `check`. Para executá-los é necessário ter o `check` instalado e
executar:

```shell
make test
```

Para instalar o Framework `check`, recorra a sua
[documentação](https://github.com/libcheck/check).

## Referência

Para consulta, uma [cheatsheet](cheatsheet.pdf) com a API da biblioteca está disponível.

