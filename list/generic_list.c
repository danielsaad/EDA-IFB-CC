#include "generic_list.h"
#include "../utils/alloc.h"
#include <assert.h>

/** Protótipos internos **/

/**
 * @brief list_new_node Cria um novo nó da lista com base no construtor.
 * @param data Ponteiro para dado a ser construído.
 * @param constructor Função construtora que atuará no dado.
 * @return Novo nó da lista com dado inserido.
 */
static generic_list_node_t *
generic_list_new_node(void *data, generic_list_node_constructor_fn constructor);

/**
 * @brief list_delete_node Remove um nó de lista e desaloca seus dados
 * internos ao chamar a função destrutora.
 * @param n Nó da lista.
 * @param destructor Função destrutora.
 */
static void
generic_list_delete_node(generic_list_node_t *n,
                         generic_list_node_destructor_fn destructor);

/** Cria o nó de uma lista **/
static generic_list_node_t *
generic_list_new_node(void *data,
                      generic_list_node_constructor_fn constructor) {
    /** aloca espaço para novo nó **/
    generic_list_node_t *new_node = mallocx(sizeof(generic_list_node_t));
    /** Constrói o novo dado através da função construtora **/
    new_node->data = constructor(data);
    /** Atribui o ponteiro para o próximo como NULL **/
    new_node->next = NULL;
    /** Retorna o nó alocado **/
    return new_node;
}

/** Deleta o nó de uma lista **/
static void
generic_list_delete_node(generic_list_node_t *n,
                         generic_list_node_destructor_fn destructor) {
    /** Chama a função destrutora para o dado do nó **/
    destructor(n->data);
    /** Libera o nó **/
    free(n);
}

/** Inicialização dos membros de uma lista **/
void generic_list_initialize(generic_list_t **l,
                             generic_list_node_constructor_fn constructor,
                             generic_list_node_destructor_fn destructor) {
    /** Aloca espaço para a estrutura lista **/
    (*l) = mallocx(sizeof(generic_list_t));
    /** Cabeça aponta para NULL**/
    (*l)->head = NULL;
    /** Cauda aponta para NULL**/
    (*l)->tail = NULL;
    /** Tamanho de uma lista recém inicializada é 0 **/
    (*l)->size = 0;
    /** Atribuição da função construtora **/
    (*l)->constructor = constructor;
    /** Atribuição da função destrutora **/
    (*l)->destructor = destructor;
}

/** Deleta uma lista com sucessivas remoções da cabeça **/
void generic_list_delete(generic_list_t **l) {
    /** Enquanto a lista não for fazia, remove a cabeça **/
    while (!generic_list_empty(*l)) {
        generic_list_remove_head(*l);
    }
    /** Desaloca espaço para a estrutura de dados **/
    free(*l);
    /** Atribui NULL ao ponteiro para nossa lista **/
    *l = NULL;
}

/** Insere um novo dado na lista com base na posição i **/
void generic_list_insert(generic_list_t *l, void *data, size_t i) {
    /** Apenas modo debug, aborta o programa se a posição for inválida **/
    assert(i <= generic_list_size(l));
    /** Se a lista está vazia, ou a posição de inserção é a 0, a
        inserção é feita na cabeça **/
    if (generic_list_empty(l) || i == 0) {
        generic_list_prepend(l, data);
    }
    /** Inserção na cauda **/
    else if (i == generic_list_size(l)) {
        generic_list_append(l, data);
    }
    /** Inserção no meio da lista que tem pelo menos 1 elemento **/
    else {
        /** Cria o novo nó ao chamar a função list_new_node **/
        generic_list_node_t *new_node =
            generic_list_new_node(data, l->constructor);
        /** Precisamos encontrar o elemento que antecede a posição i ao
         * caminhar na lista **/
        generic_list_iterator_t it = l->head;
        size_t k;
        /** Caminhamos até a posição i-1 da lista **/
        for (k = 0; k < i - 1; k++) {
            it = it->next;
        }
        /** it agora aponta pro elemento da posição i-1*/
        /** Estabelecemos o next do novo nó para o elemento antigo da
         * da posição i **/
        new_node->next = it->next;
        /** O next do nó da posição i-1 recebe o elemento recém inserido **/
        it->next = new_node;
        /** O tamanho da lista é incrementado **/
        l->size++;
    }
}

/** Insere um elemento na cabeça da lista **/
void generic_list_prepend(generic_list_t *l, void *data) {
    /** Cria um novo nó ao invocar list_new_node **/
    generic_list_node_t *new_node = generic_list_new_node(data, l->constructor);
    /** Novo nó estabelece uma ligação para a cabeça antiga **/
    new_node->next = l->head;
    /** Cabeça antiga aponta agora para o nó recém criado **/
    l->head = new_node;
    /** Se a lista estava vazia, a cauda também deve apontar para o nó recém
     * criado **/
    if (generic_list_empty(l)) {
        l->tail = new_node;
    }
    /** O tamanho da lista é incrementado **/
    l->size++;
}

/** Insere um elemento na cauda da lista **/
void generic_list_append(generic_list_t *l, void *data) {
    /** Cria o novo nó ao chamar list_new_node **/
    generic_list_node_t *new_node = generic_list_new_node(data, l->constructor);
    /** Se a lista está vazia, a cabeça deve apontar para o nó recém criado **/
    if (generic_list_empty(l)) {
        l->head = new_node;
    }
    /** Caso contrário, a lista possui uma cauda e ela deve estabelecer
     * uma ligação o elemento recém criado **/
    else {
        l->tail->next = new_node;
    }
    /** A cauda é atualizada para apontar para o elemento recém criado **/
    l->tail = new_node;
    /** O tamanho da lista é incrementado **/
    l->size++;
}

/** Remove o elemento da posição i da lista **/
void generic_list_remove(generic_list_t *l, size_t i) {
    /** Debug apenas, aborta o programa se a remoção estiver sendo feita
     * em uma lista vazia ou em uma posição inexistente da lista **/
    assert(!generic_list_empty(l) && i < generic_list_size(l));
    /** Se a lista tem tamanho 1, ou a remoção é do primeiro elemento,
        equivale a eliminar a cabeça
    **/
    if (generic_list_size(l) == 1 || i == 0) {
        generic_list_remove_head(l);
    }
    /** Se i==generic_list_size(l)-1, a remoção é na cauda **/
    else if (i == generic_list_size(l) - 1) {
        generic_list_remove_tail(l);
    }
    /** O nó a ser removido encontra-se no meio da lista e a lista
        possuir mais que um elemento **/
    else {
        /** Nó a ser removido **/
        generic_list_node_t *node;
        /** Devemos percorrer até o i-1-ésimo elemento a partir
         * da cabeça **/
        generic_list_iterator_t it = l->head;
        size_t k;
        /** Itera-se até o elemento imediatamente interior ao elemento i **/
        for (k = 0; k < i - 1; k++) {
            it = it->next;
        }
        /** Nó a ser removido passa a ser o i-ésimo elemento **/
        node = it->next;
        /** O anterior ao nó a ser removido aponta para o elemento
         * que vem após o nó a ser removido **/
        it->next = node->next;
        /** Deleta o nó atribuido anteriormente **/
        generic_list_delete_node(node, l->destructor);
        /** Decrementa o tamanho da lista **/
        l->size--;
    }
}

/** Remove a cabeça da lista **/
void generic_list_remove_head(generic_list_t *l) {
    /** Debug apenas: aborta o programa caso a remoção da cabeça seja sobre
     * uma lista vazia **/
    assert(!generic_list_empty(l));
    /** O nó a ser removido recebe a cabeça **/
    generic_list_iterator_t node = l->head;
    /** Se a lista tem um elemento, após a remoção a cauda deve ser NULL **/
    if (generic_list_size(l) == 1) {
        l->tail = NULL;
    }
    /** A cabeça passa para o próximo elemento **/
    l->head = l->head->next;
    /** Deleta-se a cabeça **/
    generic_list_delete_node(node, l->destructor);
    /** O tamanho da lista é decrementado **/
    l->size--;
}

/** Remove a cauda da lista **/
void generic_list_remove_tail(generic_list_t *l) {
    /** Debug apenas,aborta o programa caso a função seja chamada para uma
     * lista vazia **/
    assert(generic_list_size(l) > 0);
    /** O nó a ser removido recebe a cauda **/
    generic_list_iterator_t node = l->tail;
    /** Se a lista tem tamanho 1, a cauda e a cabeça apontam para NULL
     * após a remoção **/
    if (generic_list_size(l) == 1) {
        l->head = NULL;
        l->tail = NULL;
    }
    /** Caso contrário, a lista tem mais de um elemento. Deve-se iterar sobre
     * a lista até o penúltimo elemento **/
    else {
        /** Itera-se sobre a lista a partir da cabeça até o penúltimo elemento
         **/
        generic_list_iterator_t it = l->head;
        while (it->next != l->tail) {
            it = it->next;
        }
        /** O campo next do penúltimo elemento agora aponta para NULL **/
        it->next = NULL;
        /** O penúltimo elemento passa a ser a cauda **/
        l->tail = it;
    }
    /** Remove-se a cauda antiga **/
    generic_list_delete_node(node, l->destructor);
    /** O tamanho da lista é decrementado **/
    l->size--;
}

/** Acessa o i-ésimo elemento da lista **/
void *generic_list_access(generic_list_t *l, size_t i) {
    /** Debug apenas, aborta o programa em caso de posição inválida
     * a ser acessada **/
    assert(!generic_list_empty(l) && i < generic_list_size(l));
    /** Se i==0, o acesso é na cabeça **/
    if (i == 0) {
        return (generic_list_access_head(l));
    }
    /** Se i==generic_list_size(l)-1, o acesso é na cauda **/
    else if (i == generic_list_size(l) - 1) {
        return (generic_list_access_tail(l));
    }
    /** Caso contrário, percorre-se a lista até o i-ésimo elemento **/
    size_t j;
    generic_list_iterator_t it = l->head;
    for (j = 0; j < i; j++) {
        it = it->next;
    }
    /** O campo dado do elemento acessado é retornado **/
    return (it->data);
}

/** Acessa a cabeça da lista **/
void *generic_list_access_head(generic_list_t *l) {
    /** Debug apenas, aborta o programa se a lista não tem cabeça (é vazia) **/
    assert(!(generic_list_empty(l)));
    return (l->head->data);
}

/** Acessa a cauda da lista **/
void *generic_list_access_tail(generic_list_t *l) {
    /** Debug apenas, aborta o programa se a lista não tem cauda (é vazia)**/
    assert(!generic_list_empty(l));
    return (l->tail->data);
}

/** Retorna o tamanho da lista **/
size_t generic_list_size(generic_list_t *l) {
    return l->size;
}

/** Retorna verdadeiro se a lista está vazia, e falso caso contrário **/
bool generic_list_empty(generic_list_t *l) {
    return generic_list_size(l) == 0 ? 1 : 0;
}
