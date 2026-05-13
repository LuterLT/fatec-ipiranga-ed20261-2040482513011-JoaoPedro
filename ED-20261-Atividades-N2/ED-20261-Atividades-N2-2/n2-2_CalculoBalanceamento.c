/* ============================================================================
 * Fatec Ipiranga - Disciplina: Estrutura de Dados - Prof. Verissimo
 * Atividade N2-2: Calculando Fator de Balanceamente (AVL)
 * Aluno: João Pedro de França Assalti
 * RA: 2040482513011
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int valor;
    int altura;
    
    struct No *esq;
    struct No *dir;
} No;

int max(int a, int b) {
    return (a > b) ? a : b;
}
int min(int a, int b) {
    return (a < b) ? a : b;
}

int calcularAltura(No *n){
    if(n == NULL){
        return -1;
    }
    return 1 + max(calcularAltura(n->esq), calcularAltura(n->dir));
}


int obterFB(struct No *n){ //formula Eh - Dh
    return calcularAltura(n->esq) - calcularAltura(n->dir);
}

int main()
{
    No *raiz = malloc(sizeof(No));
    No *no10  = malloc(sizeof(No));
    No *no5   = malloc(sizeof(No));
    No *no2   = malloc(sizeof(No));

    // Configurando a raiz (20)
    raiz->valor = 20;
    raiz->altura = 0;
    raiz->esq = no10;
    raiz->dir = NULL;

    // Configurando o nó 10
    no10->valor = 10;
    no10->altura = 0;
    no10->esq = no5;
    no10->dir = NULL;

    // Configurando o nó 5
    no5->valor = 5;
    no5->altura = 0;
    no5->esq = no2;
    no5->dir = NULL;

    // Configurando o nó 2 (folha)
    no2->valor = 2;
    no2->altura = 0;
    no2->esq = NULL;
    no2->dir = NULL;
    
    printf("Altura da arvore: %d\n", calcularAltura(raiz));
    printf("Calcular FB da raiz: %d\n", obterFB(raiz));

    return 0;
}
