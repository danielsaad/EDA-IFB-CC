#include "list.h"
#include "../utils/alloc.h"
#include <assert.h>

/** Protótipos internos **/

/**
 * @brief list_new_node Cria um novo nó da lista.
 * @param data Dado do novo nó.
 * @return Novo nó da lista com dado inserido.
 */
static list_node_t *list_new_node(int data);

/**
 * @brief list_delete_node Remove um nó de lista.
 * @param n Nó da lista.
 */
static void list_delete_node(list_node_t *n);

/** Cria o nó de uma lista **/
static list_node_t *list_new_node(int data) {
    /** aloca espaço para novo nó **/
    list_node_t *new_node = mallocx(sizeof(list_node_t));
    /** Constrói o novo dado através da função construtora **/
    new_node->data = data;
    /** Atribui o ponteiro para o próximo como NULL **/
    new_node->next = NULL;
    /** Retorna o nó alocado **/
    return new_node;
}

/** Deleta o nó de uma lista **/
static void list_delete_node(list_node_t *n) {
    /** Libera o nó **/
    free(n);
}

/** Inicialização dos membros de uma lista **/
void list_initialize(list_t **l) {
    /** Aloca espaço para a estrutura lista **/
    (*l) = mallocx(sizeof(list_t));
    /** Cabeça aponta para NULL**/
    (*l)->head = NULL;
    /** Cauda aponta para NULL**/
    (*l)->tail = NULL;
    /** Tamanho de uma lista recém inicializada é 0 **/
    (*l)->size = 0;
}

/** Deleta uma lista com sucessivas remoções da cabeça **/
void list_delete(list_t **l) {
    /** Enquanto a lista não for fazia, remove a cabeça **/
    while (!list_empty(*l)) {
        list_remove_head(*l);
    }
    /** Desaloca espaço para a estrutura de dados **/
    free(*l);
    /** Atribui o valor NULL ao ponteiro da lista **/
    *l = NULL;
}

/** Insere um novo dado na lista com base na posição i **/
void list_insert(list_t *l, int data, size_t i) {
    /** Apenas modo debug, aborta o programa se a posição for inválida **/
    assert(i <= list_size(l));
    /** Se a lista está vazia, ou a posição de inserção é a 0, a
        inserção é feita na cabeça **/
    if (list_empty(l) || i == 0) {
        list_prepend(l, data);
    }
    /** Inserção na cauda **/
    else if (i == list_size(l)) {
        list_append(l, data);
    }
    /** Inserção no meio da lista que tem pelo menos 1 elemento **/
    else {
        /** Cria o novo nó ao chamar a função list_new_node **/
        list_node_t *new_node = list_new_node(data);
        /** Precisamos encontrar o elemento que antecede a posição i ao
         * caminhar na lista **/
        list_node_t *aux = l->head;
        size_t k;
        /** Caminhamos até a posição i-1 da lista **/
        for (k = 0; k < i - 1; k++) {
            aux = aux->next;
        }
        /** it agora aponta pro elemento da posição i-1*/
        /** Estabelecemos o next do novo nó para o elemento antigo da
         * da posição i **/
        new_node->next = aux->next;
        /** O next do nó da posição i-1 recebe o elemento recém inserido **/
        aux->next = new_node;
        /** O tamanho da lista é incrementado **/
        l->size++;
    }
}

/** Insere um elemento na cabeça da lista **/
void list_prepend(list_t *l, int data) {
    /** Cria um novo nó ao invocar list_new_node **/
    list_node_t *new_node = list_new_node(data);
    /** Novo nó estabelece uma ligação para a cabeça antiga **/
    new_node->next = l->head;
    /** Cabeça antiga aponta agora para o nó recém criado **/
    l->head = new_node;
    /** Se a lista estava vazia, a cauda também deve apontar para o nó recém
     * criado **/
    if (list_empty(l)) {
        l->tail = new_node;
    }
    /** O tamanho da lista é incrementado **/
    l->size++;
}

/** Insere um elemento na cauda da lista **/
void list_append(list_t *l, int data) {
    /** Cria o novo nó ao chamar list_new_node **/
    list_node_t *new_node = list_new_node(data);
    /** Se a lista está vazia, a cabeça deve apontar para o nó recém criado **/
    if (list_empty(l)) {
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
void list_remove(list_t *l, size_t i) {
    /** Debug apenas, aborta o programa se a remoção estiver sendo feita
     * em uma lista vazia ou em uma posição inexistente da lista **/
    assert(!list_empty(l) && i < list_size(l));
    /** Se a lista tem tamanho 1, ou a remoção é do primeiro elemento,
        equivale a eliminar a cabeça
    **/
    if (list_size(l) == 1 || i == 0) {
        list_remove_head(l);
    }
    /** Se i==list_size(l)-1, a remoção é na cauda **/
    else if (i == list_size(l) - 1) {
        list_remove_tail(l);
    }
    /** O nó a ser removido encontra-se no meio da lista e a lista
        possuir mais que um elemento **/
    else {
        /** Nó a ser removido **/
        list_node_t *node;
        /** Devemos percorrer até o i-1-ésimo elemento a partir
         * da cabeça **/
        list_node_t *aux = l->head;
        size_t k;
        /** Itera-se até o elemento imediatamente interior ao elemento i **/
        for (k = 0; k < i - 1; k++) {
            aux = aux->next;
        }
        /** Nó a ser removido passa a ser o i-ésimo elemento **/
        node = aux->next;
        /** O anterior ao nó a ser removido aponta para o elemento
         * que vem após o nó a ser removido **/
        aux->next = node->next;
        /** Deleta o nó atribuido anteriormente **/
        list_delete_node(node);
        /** Decrementa o tamanho da lista **/
        l->size--;
    }
}

/** Remove a cabeça da lista **/
void list_remove_head(list_t *l) {
    /** Debug apenas: aborta o programa caso a remoção da cabeça seja sobre
     * uma lista vazia **/
    assert(!list_empty(l));
    /** O nó a ser removido recebe a cabeça **/
    list_node_t *aux = l->head;
    /** Se a lista tem um elemento, após a remoção a cauda deve ser NULL **/
    if (list_size(l) == 1) {
        l->tail = NULL;
    }
    /** A cabeça passa para o próximo elemento **/
    l->head = l->head->next;
    /** Deleta-se a cabeça **/
    list_delete_node(aux);
    /** O tamanho da lista é decrementado **/
    l->size--;
}

/** Remove a cauda da lista **/
void list_remove_tail(list_t *l) {
    /** Debug apenas,aborta o programa caso a função seja chamada para uma
     * lista vazia **/
    assert(list_size(l) > 0);
    /** O nó a ser removido recebe a cauda **/
    list_node_t *to_be_removed = l->tail;
    /** Se a lista tem tamanho 1, a cauda e a cabeça apontam para NULL
     * após a remoção **/
    if (list_size(l) == 1) {
        l->head = NULL;
        l->tail = NULL;
    }
    /** Caso contrário, a lista tem mais de um elemento. Deve-se iterar sobre
     * a lista até o penúltimo elemento **/
    else {
        /** Itera-se sobre a lista a partir da cabeça até o penúltimo elemento
         **/
        list_node_t *aux = l->head;
        while (aux->next != l->tail) {
            aux = aux->next;
        }
        /** O campo next do penúltimo elemento agora aponta para NULL **/
        aux->next = NULL;
        /** O penúltimo elemento passa a ser a cauda **/
        l->tail = aux;
    }
    /** Remove-se a cauda antiga **/
    list_delete_node(to_be_removed);
    /** O tamanho da lista é decrementado **/
    l->size--;
}

/** Acessa o i-ésimo elemento da lista **/
int list_access(list_t *l, size_t i) {
    /** Debug apenas, aborta o programa em caso de posição inválida
     * a ser acessada **/
    assert(!list_empty(l) && i < list_size(l));
    /** Se i==0, o acesso é na cabeça **/
    if (i == 0) {
        return (list_access_head(l));
    }
    /** Se i==list_size(l)-1, o acesso é na cauda **/
    else if (i == list_size(l) - 1) {
        return (list_access_tail(l));
    }
    /** Caso contrário, percorre-se a lista até o i-ésimo elemento **/
    size_t j;
    list_node_t *it = l->head;
    for (j = 0; j < i; j++) {
        it = it->next;
    }
    /** O campo dado do elemento acessado é retornado **/
    return (it->data);
}

/** Acessa a cabeça da lista **/
int list_access_head(list_t *l) {
    /** Debug apenas, aborta o programa se a lista não tem cabeça (é vazia) **/
    assert(!(list_empty(l)));
    return (l->head->data);
}

/** Acessa a cauda da lista **/
int list_access_tail(list_t *l) {
    /** Debug apenas, aborta o programa se a lista não tem cauda (é vazia)**/
    assert(!list_empty(l));
    return (l->tail->data);
}

/** Retorna o tamanho da lista **/
size_t list_size(list_t *l) {
    return l->size;
}

/** Retorna verdadeiro se a lista está vazia, e falso caso contrário **/
bool list_empty(list_t *l) {
    return list_size(l) == 0 ? 1 : 0;
}
