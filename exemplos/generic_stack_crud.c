#include "alloc.h"
#include "generic_stack.h"
#include <stdio.h>
#include <string.h>

typedef struct pessoa {
    char nome[30];
    char cpf[20];
    int idade;
} pessoa;

void *constructor_pessoa(void *data) {
    void *ptr = mallocx(sizeof(pessoa));
    memcpy(ptr, data, sizeof(pessoa));
    return ptr;
}

void my_getline(char *str, size_t size) {
    int i;
    char c;
    for (i = 0; i < size - 1; i++) {
        c = getchar();
        if (c == '\n') {
            str[i] = '\0';
            break;
        }
        str[i] = c;
    }
    str[size - 1] = '\0';
    while (c != '\n') {
        c = getchar();
    }
}

void destructor_pessoa(void *data) {
    free(data);
}

void cadastra_pessoa(pessoa *p) {
    printf("Nome: ");
    my_getline(p->nome, 30);
    printf("CPF: ");
    my_getline(p->cpf, 20);
    printf("Idade: ");
    scanf("%d%*c", &p->idade);
}

void imprime_pessoa(const pessoa *p) {
    printf("Nome: ");
    printf("%s\n", p->nome);
    printf("CPF: ");
    printf("%s\n", p->cpf);
    printf("Idade: ");
    printf("%d\n", p->idade);
}

int main(void) {
    int i;
    generic_stack_t *s;
    pessoa p;
    generic_stack_initialize(&s, constructor_pessoa, destructor_pessoa);
    for (i = 0; i < 5; i++) {
        printf("Cadastrando pessoa %d\n", i + 1);
        cadastra_pessoa(&p);
        generic_stack_push(s, &p);
    }
    while (!generic_stack_empty(s)) {
        printf("\n**Imprimindo pessoa**\n");
        p = *(pessoa *)generic_stack_top(s);
        generic_stack_pop(s);
        imprime_pessoa(&p);

        printf("\n");
    }
    generic_stack_delete(&s);
    return 0;
}
