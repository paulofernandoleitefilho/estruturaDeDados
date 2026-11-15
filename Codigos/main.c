#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó
typedef struct Node {
    int valor;
    struct Node *next;
} Node;

// Inicialização da lista
Node *lista = NULL;

// INSERT: inserir elemento no início
void insert(int valor) {

    Node *novo = (Node*) malloc(sizeof(Node));

    if (novo == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return;
    }

    novo->valor = valor;
    novo->next = lista;

    lista = novo;

    printf("Elemento %d inserido!\n", valor);
}

// REMOVE: remover elemento pelo valor
void removeNode(int valor) {

    Node *atual = lista;
    Node *anterior = NULL;

    while (atual != NULL && atual->valor != valor) {
        anterior = atual;
        atual = atual->next;
    }

    if (atual == NULL) {
        printf("Elemento %d nao encontrado!\n", valor);
        return;
    }

    if (anterior == NULL) {
        lista = atual->next;
    } else {
        anterior->next = atual->next;
    }

    free(atual);

    printf("Elemento %d removido!\n", valor);
}

// DELETAR: excluir toda a lista
void deletar() {

    Node *atual = lista;
    Node *proximo;

    while (atual != NULL) {

        proximo = atual->next;

        free(atual);

        atual = proximo;
    }

    lista = NULL;

    printf("Lista completamente deletada!\n");
}

// Exibir elementos da lista
void display() {

    Node *atual = lista;

    printf("\nLista: ");

    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->next;
    }

    printf("NULL\n");
}


int main() {

    int opcao;
    int valor;

    do {

        printf("\n========== MENU LISTA ENCADEADA ==========\n");
        printf("1 - Inserir elemento\n");
        printf("2 - Remover elemento\n");
        printf("3 - Visualizar lista\n");
        printf("4 - Deletar lista completa\n");
        printf("0 - Sair\n");
        printf("==========================================\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                printf("Digite o valor para inserir: ");
                scanf("%d", &valor);

                insert(valor);

                printf("\nLista atualizada:\n");
                display();
                break;

            case 2:
                printf("Digite o valor para remover: ");
                scanf("%d", &valor);

                removeNode(valor);

                printf("\nLista atualizada:\n");
                display();
                break;

            case 3:
                printf("\nVisualizacao da lista:\n");
                display();
                break;

            case 4:
                deletar();

                printf("\nLista atualizada:\n");
                display();
                break;

            case 0:
                printf("\nEncerrando programa...\n");
                deletar();
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
